// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include <SDKDDKVer.h>


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRT_SECURE_NO_WARNINGS
// Windows Header Files:
#include <windows.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <ctime>
#include "MinHook.h""
#include <D3D11.h>
#include <D3DCompiler.h>

#include "../GhostsAzza/detours/detours64.h"

#include "vthook.h"
#include "vector.h"
#include "Structs.h"
#include "Utils.h"
#include "D3DHook.h"
#include "Toggles.h"
#include "GameMenu.h"
#include "Engine.h"
#include "DLCUnlock.h"
#include "SlowmoHandler.h"
#include "Hooks.h"
#include "../GhostsAzza/Imgui/imgui.h"
#include "../GhostsAzza/Imgui/imgui_impl_dx11.h"
#include "Menu.h"
#include "InputHook.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, __FILE__"\\..\\detours\\detours64.lib")




// TODO: reference additional headers your program requires here
