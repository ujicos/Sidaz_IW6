#include "stdafx.h"

/*typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

typedef LRESULT(__fastcall* tWndProcc)(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
tWndProcc oWndProc;

ID3D11Device *pDevice = NULL;
ID3D11DeviceContext *pContext = NULL;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pDeviceContextVTable = NULL;

D3D11PresentHook phookD3D11Present = NULL;
D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11ClearRenderTargetViewHook phookD3D11ClearRenderTargetView = NULL;
ID3D11RenderTargetView*  g_pRenderTargetView = NULL;


typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall *D3D11CreateQueryHook) (ID3D11Device* pDevice, const D3D11_QUERY_DESC *pQueryDesc, ID3D11Query **ppQuery);
typedef void(__stdcall *D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView *const *ppShaderResourceViews);
typedef void(__stdcall *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

static HWND                     g_hWnd = nullptr;
static HMODULE					g_hModule = nullptr;
static ID3D11Device*            g_pd3dDevice = nullptr;
static ID3D11DeviceContext*     g_pd3dContext = nullptr;
static IDXGISwapChain*          g_pSwapChain = nullptr;
static std::once_flag           g_isInitialized;

D3D11PresentHook                phookD3D11Present = nullptr;
D3D11DrawIndexedHook            phookD3D11DrawIndexed = nullptr;
D3D11CreateQueryHook			phookD3D11CreateQuery = nullptr;
D3D11PSSetShaderResourcesHook	phookD3D11PSSetShaderResources = nullptr;
D3D11ClearRenderTargetViewHook  phookD3D11ClearRenderTargetViewHook = nullptr;

DWORD_PTR*                         pSwapChainVTable = nullptr;
DWORD_PTR*						   pDeviceVTable = nullptr;
DWORD_PTR*                         pDeviceContextVTable = nullptr;

HWND hWnd;
bool firstTime = true;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI hk_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		if (pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
		}
		break;
	case WM_KEYDOWN:
		Toggles.HandleKeys(wParam);
		break;
	}

	if (!firstTime)
	{
		ImGui::GetIO().MouseDrawCursor = Toggles.HostMenu || Toggles.ModMenu;
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		if (Toggles.HostMenu || Toggles.ModMenu)
			return true;
	}
	
	return oWndProc(hWnd, msg, wParam, lParam);
}

HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	/*if (firstTime)
	{
		pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pContext);

		//ID3D11Texture2D* renderTargetTexture = nullptr;

		//if (SUCCEEDED(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&renderTargetTexture))))
		//{
		//	pDevice->CreateRenderTargetView(renderTargetTexture, NULL, &g_pRenderTargetView);
		//	renderTargetTexture->Release();
		//}

		ImGui::CreateContext();
		ImGui_ImplDX11_Init(hWnd, pDevice, pContext);
		GameMenu::SetupMenu();
		ImGui_ImplDX11_CreateDeviceObjects();
		
		firstTime = false;
	}

	if (Toggles.HostMenu || Toggles.ModMenu)
	{
		//pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);


		ImGui_ImplDX11_NewFrame();
		GameMenu::DrawMenu();
		ImGui::Render();


		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	//pContext->Flush();

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

void __stdcall hookD3D11ClearRenderTargetView(ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4])
{
	phookD3D11ClearRenderTargetView(pContext, pRenderTargetView, ColorRGBA);
	ImGui_ImplDX11_CreateDeviceObjects();
}

void* DetourFunc64(byte* origFunc, byte* hooKFunc)
{
	void* ret = 0;
	MH_CreateHook((void*)origFunc, (void*)hooKFunc, (LPVOID*)&ret);
	MH_EnableHook((void*)origFunc);
	return ret;
}

void RemoveDetour64(byte* origFunc)
{
	MH_RemoveHook(origFunc);
}

void InitializeHook()
{
	hWnd = *(HWND*)0x147AD2640;
	IDXGISwapChain* pSwapChain;

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = GetWindowLongA(hWnd, GWL_STYLE) & WS_POPUP != 0 ? FALSE : TRUE;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	
	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext)))
	{
		printf("Failed to create directX device and swapchain stupid nigga!\n");
		return;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pDeviceContextVTable = (DWORD_PTR*)pContext;
	pDeviceContextVTable = (DWORD_PTR*)pDeviceContextVTable[0];

	

	DWORD old_protect;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &old_protect);

	oWndProc = (tWndProcc)DetourFunc64((BYTE*)0x140504A00, (BYTE*)hk_WndProc);

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	return;
}

void D3DHook::Hook()
{
	InitializeHook();
}*/