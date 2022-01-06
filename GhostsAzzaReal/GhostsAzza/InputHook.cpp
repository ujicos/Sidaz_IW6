#include "stdafx.h"
#include "InputHook.h"
#include "Menu.h"

using namespace ImGui;

WNDPROC	oWndProc;

ID3D11Device *pDevice = NULL;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InputHook::Init(HWND hWindow)
{
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
}

void InputHook::Remove(HWND hWindow)
{
	SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}

Menu menu1 = Menu();

LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	

	//if (!menu1.IsOpen)

	//if (!Toggles.HostMenu)
		//return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);

	//ImGui::GetIO().MouseDrawCursor = menu1.IsOpen;
		//return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
	

	//ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
	
	//ImGui::GetIO().MouseDrawCursor = Toggles.HostMenu || Toggles.ModMenu || Toggles.menuaw;
	
	//ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
	//if (menu1.IsOpen)
	//	return ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);


	switch (uMsg)
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

	


	if (!Toggles.HostMenu)
		return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);

	
	
	ImGui::GetIO().MouseDrawCursor = menu1.IsOpen;
	ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
	if (menu1.IsOpen)
		return true;
	
	if (wParam == VK_LBUTTON && Toggles.HostMenu)
		return -1;

	/*switch (uMsg)
	{
		
	case WM_LBUTTONDOWN:
		GetIO().MouseDown[0] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		GetIO().MouseDown[0] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONDOWN:
		GetIO().MouseDown[1] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_RBUTTONUP:
		GetIO().MouseDown[1] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONDOWN:
		GetIO().MouseDown[2] = true; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MBUTTONUP:
		GetIO().MouseDown[2] = false; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEWHEEL:
		GetIO().MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f; return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		GetIO().MousePos.x = (signed short)(lParam); GetIO().MousePos.y = (signed short)(lParam >> 16); return DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}*/

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

