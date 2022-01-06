#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <Windows.h>
#include "IW6.h"
#include <string>
#include <cmath>

//#define _CRT_SECURE_NO_WARNINGS

#define MAXKNOCKBACK 99999
#define MINKNOCKBACK 0
#define MAXEB 10000
#define MINEB 0

typedef unsigned char byte;



unsigned char moveaxrifle[] = { 0xB8, 0x02, 0x00, 0x00, 0x00,0x90, 0x90 };
unsigned char movecxrifle[] = { 0xB9, 0x02, 0x00, 0x00, 0x00,0x90, 0x90 };
DWORD_PTR damageeaxpatches[] = { 0x140394E37,0x140394EA0,0x140394FD2,0x140395060,0x14039512A,0x1403951C9 };
DWORD_PTR damageecxpatches[] = { 0x140395227 };
unsigned char defaulteaxrifle[ARRAYSIZE(damageeaxpatches)][ARRAYSIZE(moveaxrifle)];
unsigned char defaultecxrifle[ARRAYSIZE(damageecxpatches)][ARRAYSIZE(movecxrifle)];
 

unsigned char movzxebphitloc[] = { 0xBD, 0x04, 0x00, 0x00, 0x00,0x90,0x90,0x90 };
DWORD_PTR hitlocmovzxpatches[] = { 0x140394E0A,0x140394F5B };
unsigned char defaultmovzxebphitloce[ARRAYSIZE(hitlocmovzxpatches)][ARRAYSIZE(movzxebphitloc)];




void PatchAddy(DWORD_PTR address, unsigned char* buffer, size_t size)
{
	DWORD one, two;
	VirtualProtect((void*)address, size, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)address, buffer, size);
	VirtualProtect((void*)address, size, one, &two);
}

void CopyDamage()
{
	for (int i = 0; i < ARRAYSIZE(damageeaxpatches); i++)
		memcpy((void*)defaulteaxrifle[i], (void*)damageeaxpatches[i], ARRAYSIZE(moveaxrifle));

	for (int i = 0; i < ARRAYSIZE(damageecxpatches); i++)
		memcpy((void*)defaultecxrifle[i], (void*)damageecxpatches[i], ARRAYSIZE(movecxrifle));

	for (int i = 0; i < ARRAYSIZE(hitlocmovzxpatches); i++)
		memcpy((void*)defaultmovzxebphitloce[i], (void*)hitlocmovzxpatches[i], ARRAYSIZE(movzxebphitloc));
}

void PatchDamage()
{
	for (int i = 0; i < ARRAYSIZE(damageeaxpatches); i++)
		PatchAddy(damageeaxpatches[i], moveaxrifle, ARRAYSIZE(moveaxrifle));

	for (int i = 0; i < ARRAYSIZE(damageecxpatches); i++)
		PatchAddy(damageecxpatches[i],movecxrifle, ARRAYSIZE(movecxrifle));

	for (int i = 0; i < ARRAYSIZE(hitlocmovzxpatches); i++)
		PatchAddy(hitlocmovzxpatches[i], movzxebphitloc, ARRAYSIZE(movzxebphitloc));
}

void UnpatchDamage()
{
	for (int i = 0; i < ARRAYSIZE(damageeaxpatches); i++)
		PatchAddy(damageeaxpatches[i],defaulteaxrifle[i], ARRAYSIZE(moveaxrifle));

	for (int i = 0; i < ARRAYSIZE(damageecxpatches); i++)
		PatchAddy(damageecxpatches[i], defaultecxrifle[i], ARRAYSIZE(movecxrifle));

	for (int i = 0; i < ARRAYSIZE(hitlocmovzxpatches); i++)
		PatchAddy(hitlocmovzxpatches[i], defaultmovzxebphitloce[i], ARRAYSIZE(movzxebphitloc));
}

typedef int(__cdecl* tOpenConsole)(void);
tOpenConsole OpenConsole = (tOpenConsole)0x140503130;//mw3==0x5CF550;//mw2sp= 0x4142B0;//mw2mp= 0x5CB490; 0x1405030E0==ghosts

typedef void(__cdecl* tExecuteSingleCommand)(int localClientNum, int controllerIndex, const char* text);
tExecuteSingleCommand ExecuteSingleComamnd = (tExecuteSingleCommand)0x1403F7590;//0x5461C0; //0x564760; //executesinglecommand

typedef void(__cdecl* tGameSendServerCommand)(int clientNum, int type, const char *text);
tGameSendServerCommand GameSendServerCommand = (tGameSendServerCommand)0x1404758C0;//0x573100; //gamesendservercommand definiton (use as host only)

typedef void(__cdecl* tStartMatch)(void *PartyData_s_party, int localControllerIndex);
tStartMatch StartMatch = (tStartMatch)STARTMATCHADDY;

typedef void(__cdecl* tBalanceTeams)(void *PartyData_s_party);
tBalanceTeams BalanceTeams = (tBalanceTeams)BALANCETEAMSADDY;

typedef dvar_t* (__cdecl* tFindDvar)(const char* dvarname);
tFindDvar FindDvar = (tFindDvar)0x1404ECB60;

typedef void(__cdecl* tDSGame_SetPlayerRoundResults)(int clientnum, int idk, int idk2, int idk3);
tDSGame_SetPlayerRoundResults DSGame_SetPlayerRoundResults = (tDSGame_SetPlayerRoundResults)0x1402EA860;


typedef const char*(__cdecl* tGetString)(const char *dvarName);
tGetString GetString = (tGetString)0x1404ECD80;

typedef bool(__cdecl* tOpenMenu)(int localClientNum, const char *menuName);
tOpenMenu OpenMenu_GHOSTS = (tOpenMenu)0x1404B38A0;

typedef void(__cdecl* tG_Damage)(void* a1, int *a2, int *a3, void* a4, int a5, signed int a6, int a7, char mod, int a9, char hitLoc, int a11, int a12, int a13, int a14);
tG_Damage oG_Damage;

//typedef void(__cdecl* tsomefunc)(char nigger);
//tsomefunc somefunc = (tsomefunc)0x1405516B0;

typedef void(__cdecl* tsomefunc)(int a1, int a2, int a3, int a4);
tsomefunc osomefunc;

typedef void(__cdecl* tniggerfunc)(int a1, const char * a2);
tniggerfunc oniggerfunc;

typedef void(__cdecl* tsomefunc2)(int a5, int a6, int a7, char a8, int a9, char a10, int a11, int a12, int a13, int a14);
tsomefunc2 osomefunc2;

typedef void(__cdecl* tSV_StartMap)(int clientnum, const char *map, bool mapispreloaded);
tSV_StartMap Startmap = (tSV_StartMap)0X140470170;

typedef signed __int64(__fastcall* tNetConstStrings_SV_GetNetworkDvarIndex)(dvar_t* dvar, DWORD *outdvarindex);
tNetConstStrings_SV_GetNetworkDvarIndex NetConstStrings_SV_GetNetworkDvarIndex = (tNetConstStrings_SV_GetNetworkDvarIndex)0x1403E9BC0;

typedef void(__cdecl* tmaprestart)(void);
tmaprestart maprestart = (tmaprestart)0x1403CBAF0;


typedef void(__cdecl* tSV_StartMapForParty)(int clientnum, const char *map, bool mapispreloaded);
tSV_StartMapForParty Startmapforparty = (tSV_StartMapForParty)0x1404702F0;

typedef void(__cdecl* tcm_loadmap)(const char* name, bool checksum, bool idk );
tcm_loadmap loadmap = (tcm_loadmap)0x1403E9DE0;

typedef void(__cdecl* tCBUF_AddCall)(int localClientNum, void*);
tCBUF_AddCall CBUF_AddCall = (tCBUF_AddCall)0x1403F6AD0;

dvar_t* g_scriptmainmenu = FindDvar("g_scriptmainmenu");

typedef void(__fastcall* tConbuf_AppendText)(const char *pMsg);
tConbuf_AppendText Conbuf_AppendText = (tConbuf_AppendText)0x1405028C0;

typedef void(__fastcall* tCbuf_AddText)(int localClientNum, const char *text);
tCbuf_AddText Cbuf_AddText = (tCbuf_AddText)0x1403F6B50;


unsigned long GetDvarIndex(dvar_t* dvar)
{
	unsigned long out = 0;
	NetConstStrings_SV_GetNetworkDvarIndex(dvar, &out);
	return out;
}

void SetClientDvar(int clientnum, dvar_t* dvar, const char* dvarValueString)
{
	char buf[128];
	DWORD dIndx = GetDvarIndex(dvar);
	sprintf(buf, "q %i %s", dIndx, dvarValueString);
	GameSendServerCommand(clientnum, 0, buf);
}


void* DetourFunction(void* pSource, void* pDestination, int dwLen)
{
	DWORD MinLen = 14;

	if (dwLen < MinLen)
		return NULL;

	BYTE stub[] =
	{
		0x00, 0x25, 0x00, 0x00, 0x00, 0x00,                // jmp qword ptr [$+6]
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00   // ptr
	};

	void* pTrampoline = VirtualAlloc(0, dwLen + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	DWORD dwOld = 0;
	VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);

	// trampoline
	memcpy(stub + 6, &pDestination, 8);

	memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
	memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));


	// orig 
	memcpy(stub + 6, &pTrampoline, 8);
	memcpy(pSource, stub, sizeof(stub));

	for (int i = MinLen; i < dwLen; i++)
		*(BYTE*)((DWORD_PTR)pSource + i) = 0x90;

	VirtualProtect(pSource, dwLen, dwOld, &dwOld);

	return (void*)((DWORD_PTR)pSource + dwLen);
}
void DetourRemove(void* pSource, int dwLen)
{
	DWORD MinLen = 14;

	if (dwLen < MinLen)
		return;

	if (*(WORD*)(pSource) != 0x25FF)
		return;

	void* pTrampoline = *(void**)((DWORD_PTR)pSource + 6);

	DWORD dwOld = 0;
	VirtualProtect(pSource, dwLen, PAGE_EXECUTE_READWRITE, &dwOld);

	memcpy(pSource, pTrampoline, dwLen);

	VirtualProtect(pSource, dwLen, dwOld, &dwOld);

	//I'll do the VirtualFree part later
}

struct ScoreInfo
{
	unsigned __int16 ping;
	char status;
	unsigned __int16 score;
	unsigned __int16 kills;
	unsigned __int16 deaths;
	unsigned __int16 assists;
	unsigned __int16 extrascore0;
	unsigned __int16 extrascore1;
	unsigned __int16 adrenaline;
};



//How it looks in ida


//how i remake it

ScoreInfo GetClientScoreInfo(int client)
{
	return *(ScoreInfo*)(14952 * client + *(DWORD_PTR*)0x1443F4600 + 13520 - offsetof(ScoreInfo, score)); //subtract score offset cause we want entire struct
}

void SetClientScoreInfo(int client, ScoreInfo sc)
{
	*(ScoreInfo*)(14952 * client + *(DWORD_PTR*)0x1443F4600 + 13520 - offsetof(ScoreInfo, score)) = sc; //subtract score offset cause we want entire struct
}
//-1, 1145295280, 1145296200, 2243, 1143447776, 1075911317 //debug info
//-1, 1145295280, 1145296200, 2243, 1143447776, 1075911317, 16, 141716352

HWND curWindow;
WNDPROC oldWindowProc;
//tOpenMenu OpenMenu = (tOpenMenu)OFFSET;

bool First = true;
int KnockBack = 0;
int EB = 0;
bool WelcomeDisplayed[18];

DWORD WINAPI ForceHost(LPVOID lParam)
{
	dvar_t* party_minplayers = FindDvar("party_minplayers");
	party_minplayers->current.integer = 1;
	Sleep(1000);
	ExitThread(0);
}

void IncreaseKnockBack()
{
	int i = min(KnockBack + 11111, MAXKNOCKBACK); //better way than doing shitload of ifs (limits maximum knockback to 33333)

	dvar_t* g_knockback = FindDvar("g_knockback");
	g_knockback->current.value = i;

	if (KnockBack != i) //knockback has changed
	{
		std::string pop = "c \"Knockback Increased to ^2" + std::to_string(i) + "\"";
		GameSendServerCommand(-1, 0, pop.c_str());
	}
	KnockBack = i;
}

void DecreaseKnockBack()
{
	int i = max(KnockBack - 11111, MINKNOCKBACK); //better way than doing shitload of ifs (limits minimum knockback to 0)

	dvar_t* g_knockback = FindDvar("g_knockback");
	g_knockback->current.value = i;

	if (KnockBack != i) //knockback has changed
	{
		std::string pop = "c \"Knockback Decreased to ^1" + std::to_string(i) + "\"";
		GameSendServerCommand(-1, 0, pop.c_str());
	}
	KnockBack = i;
}

void IncreaseEB()
{
	int i = min(EB + 100, MAXEB); //better way than doing shitload of ifs (limits maximum knockback to 33333)

	dvar_t* bg_bulletExplRadius = FindDvar("bg_bulletExplRadius");
	bg_bulletExplRadius->current.value = i;

	if (EB != i) //knockback has changed
	{
		std::string pop = "c \"Explosive Bullets Increased to ^2" + std::to_string(i) + "\"";
		GameSendServerCommand(-1, 0, pop.c_str());
	}
	EB = i;
}

void DecreaseEB()
{
	int i = max(EB - 100, MINEB); //better way than doing shitload of ifs (limits minimum knockback to 0)

	dvar_t* bg_bulletExplRadius = FindDvar("bg_bulletExplRadius");
	bg_bulletExplRadius->current.value = i;

	if (EB != i) //knockback has changed
	{
		std::string pop = "c \"Explosive Bullets Decreased to ^1" + std::to_string(i) + "\"";
		GameSendServerCommand(-1, 0, pop.c_str());
	}
	EB = i;
}

//-1, 1145295280, 1145296200, 2243, 1143447776, 1075911317, 16, 141716352

void hookedfunc(int a1, int a2, int a3, int a4)
{ // do yor stuff   
	printf("%i , %i , %i , %i\n", a1,a2,a3,a4);


	//%c - char, %s - string
	osomefunc(a1,a2,a3,a4); // get all 29 params (ignoring rax and these shits) and pass them to this after you filter death anims
}

//1143450032, 1143447776, 1143447776, -72, 0, -128, 0, wÍD¥ÞpN ? Ç * ┐, -839984608, 1143447553, 0, -839986572, 1143447553, 0

//1143449280, 1143447776, 1143447776, -892021576, 0, -128, 0, -892021548, -892020192, 1143447553, 0, 0, 1135869952, 0
//140437D60 addstring
//

void hookednigga(int a5, char a6, int a7, int a8, int a9, char a10, int a11, int a12, int a13, int a14)
{
	printf("%i , %i , %i , %i , %i , %i , %i , %i , %i , %i , %i , %i , %i , %i \n", a5,a6,a7,a8,a9,a10,a11,a12,a13,a14);


	//osomefunc2(a5, a6, a7, a8, a9, a10, a11, a12, a13,a14);
}

void hookedniggere(int a1, const char *a2)
{
	printf("%i , %s\n", a1, a2);


	oniggerfunc(a1, a2);
}

bool GenHeadshot() //random headshots
{
	int prob = 20; //20% chance
	int perc = rand() % 101;

	return perc <= prob;
}

void hkGDamage(void* a1, int *a2, int *a3, void* a4, int a5, signed int a6, int a7, meansOfDeath_t mod, int a9, hitLocation_t hitLoc, int a11, int a12, int a13, int a14)
{
	meansOfDeath_t newmod = mod;
	hitLocation_t newhitloc = hitLoc;

	printf("mod: %i , hitloc: %i\n", (int)newmod, (int)newhitloc);

	if (newmod == meansOfDeath_t::MOD_EXPLOSIVE_BULLET)
	{
		if (GenHeadshot())
		{
			newmod = meansOfDeath_t::MOD_HEAD_SHOT;
			newhitloc = hitLocation_t::HITLOC_HEAD;
		}
		else
		{
			newmod = meansOfDeath_t::MOD_RIFLE_BULLET;
			newhitloc = hitLocation_t::HITLOC_TORSO_UPR;
		}	
	}

	oG_Damage(a1, a2, a3, a4, a5, a6, a7, newmod, a9, newhitloc, a11, a12, a13, a14);
}

DWORD WINAPI crashniggers(LPVOID lParam)
{

	byte buf[] = { 0x73, 0x61, 0x79, 0x20, 0x22, 0x5E, 0x02, 0x15, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x22 };



	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"im crashing ur shit bitch\"");
	dvar_t* cg_chattime = FindDvar("cg_chattime");
	cg_chattime->current.integer = 0;

	Sleep(3000);
	Cbuf_AddText(0, ((char*)buf));

	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);
	Cbuf_AddText(0, "say \"get fucked cancerous niggers\"");
	Sleep(300);


	cg_chattime->current.integer = 12000;

	
	ExitThread(0);
}


void crashgssc2(int clientnum, int isreliable, const char *text)
{

	//byte buf[] = { 0x73, 0x61, 0x79, 0x20, 0x22, 0x5E, 0x02, 0x15, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x22 };

	GameSendServerCommand(clientnum, 0, "c %c");




}


DWORD WINAPI crashgssc(LPVOID lParam)
{
	GameSendServerCommand(-1, 0, "c \"^\x01Nigger\""); //first try
	GameSendServerCommand(-1, 0, "c \"^\xFF\x01Nigger2\""); //second try

	Sleep(1000);
	ExitThread(0);
}


LRESULT CALLBACK WndProcc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT ret = CallWindowProc(oldWindowProc, hwnd, uMsg, wParam, lParam);

	if (uMsg != WM_KEYDOWN)
		return ret;


	if (wParam == VK_F6)
	{
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ForceHost, 0, 0, 0);
		//printf("nigga got shot");
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)crashgssc, 0, 0, 0);
	}
	if (wParam == VK_F7)
	{
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ForceHost, 0, 0, 0);
	//	for (int i = 0; i < 18; i++)
		//{
			//DSGame_SetPlayerRoundResults(i, 1450, 1450, 1450);


		//}
	//	//CBUF_AddCall(0, SV_FastRestart);
		//dvar_t* sv_mapname = FindDvar("sv_mapname");
	//	sv_mapname->current.string = "mp_snow";

		maprestart();
		printf("nigga got shot2");
	}

	if (wParam == VK_F8)
	{

		{
			//dvar_t* sv_mapname = FindDvar("sv_mapname");
			//sv_mapname->current.string = "mp_snow";

			Startmap(0, "mp_zebra", false);
			
			//Startmapforparty(0, "mp_zebra", false);


	    }

	}
	if (wParam == VK_F9)
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)crashniggers, 0, 0, 0);

		//loadmap("mp_zebra.d3dbsp", false, false);
		//Conbuf_AppendText()




	}
	//if (wParam == VK_F6)
	//{
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ForceHost, 0, 0, 0);
	//}
	//if (wParam == VK_F7)
	//{


	//}
	//else  if (wParam == VK_F9)
	//{
	//	GameSendServerCommand(-1, 0, "c \"Anti-Leave [^2ON^7]\"");
	//	GameSendServerCommand(-1, 0, "q 20 blabla");
		//GameSendServerCommand(-1, 0, "c \"Explosive Bullets [^1Off^7]\"");
		//for (int i = 0; i < 16; i++)
			//DelEB(i);
		//osomefunc = (tsomefunc)DetourFunction((void*)0x140210AE0, (void*)hookedfunc, 10);
		//GameSendServerCommand(-1, 0, "g MP_CHANGE_CLASS_NEXT_SPAWN");

	//} if (wParam == VK_F9) //page up
	//{
		//IncreaseEB();
		//SetClientDvar(-1, g_scriptmainmenu, "blabla");

	//}


 //?

	return ret;
}

DWORD WINAPI Main(LPVOID lParam)
{
	AllocConsole(); // you need cmd console for printf lol
	freopen("CONOUT$", "w", stdout); //to be able to write shit to it

	printf("nigggg\n");

	curWindow = FindWindow(NULL, "Call of Duty® Ghosts Multiplayer");
	oldWindowProc = (WNDPROC)SetWindowLongPtr(curWindow, GWLP_WNDPROC, (LONG_PTR)WndProcc);

//do hook logic here
	osomefunc = (tsomefunc)DetourFunction((void*)0x1402EA860, (void*)hookedfunc, 15);
	//oG_Damage = (tG_Damage)DetourFunction((void*)0x140394DF0, (void*)hkGDamage, 15);
	//oniggerfunc = (tniggerfunc)DetourFunction((void*)0x1404B38A0, (void*)hookedniggere, 16);

	//CopyDamage();
	ExitThread(0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}