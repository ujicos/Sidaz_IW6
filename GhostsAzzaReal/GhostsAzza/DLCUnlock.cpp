#include "stdafx.h"

const byte moveax1ret[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3 };
byte hasdlcbackup[ARRAYSIZE(moveax1ret)];

bool DLCUnlocker::FirstRun = true;

typedef char(__fastcall* tProcessDLC)(__int64 ID, int amount, __int64 prob_size, __int64 a4);
tProcessDLC ProcessDLC = (tProcessDLC)0x1404EA930;

void DLCUnlocker::SetHasDLC(bool to)
{
	if (FirstRun)
	{
		Utils::ReadAddy(0x140586270, hasdlcbackup, ARRAYSIZE(moveax1ret));
	}
	Utils::PatchAddy(0x140586270, to ? (byte*)moveax1ret : (byte*)hasdlcbackup, ARRAYSIZE(moveax1ret));
	FirstRun = false;
}

void DLCUnlocker::SetDLCUnlock(bool to)
{
	SetHasDLC(to);
	
	if(!to)
		*(int*)0x1478E8970 = 1;

	ProcessDLC(259250, 1, 16, 16843008);
	ProcessDLC(259251, 1, 32, 63214797);
	ProcessDLC(259252, 1, 64, 63214800);
	ProcessDLC(259253, 1, 128, 63214798);
	ProcessDLC(286635, 1, 2048, 63214800);
	ProcessDLC(286636, 1, 4096, 63214799);

	
}

void DLCUnlocker::UnlockDLCUnlocks()
{
	Utils::PatchAddy(0x140402B10, (byte*)moveax1ret, ARRAYSIZE(moveax1ret));
}
