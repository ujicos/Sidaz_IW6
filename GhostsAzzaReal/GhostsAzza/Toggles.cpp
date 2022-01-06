#include "stdafx.h"

byte buf[] = { 0x73, 0x61, 0x79, 0x20, 0x22, 0x5E, 0x02, 0x15, 0x15, 0xFF, 0xFF, 0xFF, 0xFF, 0x22 };

typedef void(__fastcall* tCbuf_AddText)(int localClientNum, const char *text);
tCbuf_AddText nigger_addtext = (tCbuf_AddText)0x1403F6B50;


void Switch(bool &b)
{
	b = !b;
}

INT GetActionIndex(CONST PCHAR Action)
{
	CONST CHAR** ActionList = (CONST CHAR**)0x001409E3AB0;

	for (INT i = 0; ActionList[i]; i++)
	{
		if (_stricmp(Action, ActionList[i]) == NULL)
		{
			return i;
		}
	}

	return -1;
}



//1443F4600

void SimToggles::HandleKeys(WPARAM param)
{
	if (param == VK_INSERT)
	{
		Switch(HostMenu);
		printf("ya did get called\n");
	}
	else if (param == VK_DELETE)
	{
		Switch(ModMenu);
	}

	if (param == VK_F6)
	{
		
		nigger_addtext(0, ((char*)buf));


	}

	if (param == VK_F7)
	{
		Engine.bg_compassShowEnemies->current.enabled = !Engine.bg_compassShowEnemies->current.enabled;
	}

}

void SimToggles::Init()
{
	memset(UFO, 0, sizeof(bool) * 18);
	memset(OldUFO, 0, sizeof(bool) * 18);

	memset(EB, 0, sizeof(bool) * 18);
	memset(EB_LimitWeapons, 1, sizeof(bool) * 18);
	memset(EB_IGNORE, 0, sizeof(bool) * 18);
	memset(GodMode, 0, sizeof(bool) * 18);
	
	for (int i = 0; i < 18; i++)
		EBRADIUSplayer[i] = 1000;

	for (int i = 0; i < 18; i++)
		SavedPositions[i] = Vector(0, 0, 0);

	memset(SpawnSaved, 0, sizeof(bool) * 18);
}
