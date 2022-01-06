#pragma once

class DLCUnlocker
{
private:
	static bool FirstRun;

	static void SetHasDLC(bool to);
public:
	static void SetDLCUnlock(bool to);
	static void UnlockDLCUnlocks();
};