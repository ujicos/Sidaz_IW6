// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#include <wininet.h>
#include <stdio.h>
#include "d3d11hook.h"


#pragma comment(lib, "wininet")
#include <sstream>

SimToggles Toggles;
SimEngine Engine;


std::string real_ip()
{
	HINTERNET net = InternetOpen("IP retriever",
		INTERNET_OPEN_TYPE_PRECONFIG,
		NULL,
		NULL,
		0);

	HINTERNET conn = InternetOpenUrl(net,
		"http://myexternalip.com/raw",
		NULL,
		0,
		INTERNET_FLAG_RELOAD,
		0);

	char buffer[4096];
	DWORD read;

	InternetReadFile(conn, buffer, sizeof(buffer) / sizeof(buffer[0]), &read);
	InternetCloseHandle(net);

	return std::string(buffer, read);
}

#define DLL_EXPORT extern "C" __declspec(dllexport)


const LPCSTR AppWindowTitle = "Call of Duty® Ghosts Multiplayer"; // Targeted D11 Application Window Title.
HWND hWnd = GetForegroundWindow();
DWORD WINAPI HookGame(HMODULE hModule)
{
	//if (real_ip() == "82.11.175.151" || real_ip() == "85.148.209.255" || real_ip() == "90.230.241.99" || real_ip() == "88.88.127.207")
	ImplHookDX11_Init(hModule, FindWindow(0, AppWindowTitle));
	

	return S_OK;
}



void __fastcall sub_140213350(__int64 a1, float *a2)
{

	
}





DWORD WINAPI MainThread(HINSTANCE lparam)
{
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	Sleep(1000);

	//if (real_ip() == "82.11.175.151" || real_ip() == "85.148.209.255" || real_ip() == "90.230.241.99" || real_ip() == "88.88.127.207")
	{

		Toggles.Init();

		SimHooks::Hook();

		DLCUnlocker::UnlockDLCUnlocks();
	}


	ExitThread(0);
}

BOOL APIENTRY DllMain( HMODULE hModule,  DWORD  ul_reason_for_call,  LPVOID lpReserved	 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, 0, 0, 0);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HookGame, 0, 0, 0);


		

		
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:


	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

