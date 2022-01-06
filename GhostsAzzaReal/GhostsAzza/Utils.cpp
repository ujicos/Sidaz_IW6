#include "stdafx.h"

void Utils::PatchAddy(DWORD_PTR Address, byte * buffer, size_t length)
{
	DWORD one, two;
	VirtualProtect((void*)Address, length, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)Address, buffer, length);
	VirtualProtect((void*)Address, length, one, &two);
}


void Utils::ReadAddy(DWORD_PTR Address, byte * buffer, size_t length)
{
	DWORD one, two;
	VirtualProtect((void*)Address, length, PAGE_EXECUTE_READWRITE, &one);
	memcpy((void*)buffer, (void*)Address, length);
	VirtualProtect((void*)Address, length, one, &two);
}

void Utils::NOPAddy(DWORD_PTR Address, size_t length)
{
	byte *buf = new byte[length];
	memset(buf, 0x90, length);
	PatchAddy(Address, buf, length);
	delete[] buf;
}

bool Utils::CheckKeyState(DWORD key, int flag)
{
	clock_t	c = clock();
	static BYTE			btKeyState[0x100] = { 0 };	//1 << 0 = keystate; 1 << 1 = held down
	static clock_t		clockKeyState[0x100] = { c };

	bool	r = false;
	BYTE	btState = (GetKeyState(key) & 0x8000U) >> 0xF;
	short	wDelay = btKeyState[key] & 2 ? 0x50 : 0x200;

	if (btState)
	{
		if (flag & 1)
		{
			if (!(btKeyState[key] & 1) || c - clockKeyState[key] > wDelay)
			{
				if ((btKeyState[key] & 3) == 1)
					btKeyState[key] |= 2;
				r = true;
				clockKeyState[key] = c;
			}
		}
		else
			r = true;
	}
	else
		btKeyState[key] &= ~(2);
	//btKeyState[key]		= (btKeyState[key] & ~(1)) | btState;
	btKeyState[key] ^= (-btState ^ btKeyState[key]) & 1;
	return r;
}
