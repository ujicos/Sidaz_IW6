#include "stdafx.h"

SlowmoHandler Slowmo;

double TicksToSeconds(DWORD64 Tick)
{
	return (double)Tick / 1000.0;
}

DWORD64 SecondsToTicks(double tick)
{
	return (DWORD64)(tick*1000.0);
}

void SlowmoHandler::AddSlowmo(float length, float timeScale)
{
	EndSlowmo = GetTickCount64() + SecondsToTicks(length);
	curTimeScale = timeScale;
	curLength = length;
}

void SlowmoHandler::Update()
{
	if (curTimeScale == 1.0f)
	{
		oldTimeScale = 1.0f;
		return;
	}
		
	DWORD64 tick = GetTickCount64();

	double EndSlowmoS = TicksToSeconds(EndSlowmo);
	double TickS = TicksToSeconds(tick);
	double StartTime = EndSlowmoS - curLength;

	float StartLen = curLength / 5.0f;
	float EndLen = curLength / 3.0f;

	if (EndSlowmoS - TickS > 100.0)
	{
		Toggles.CurTimescale = 1.0f;
		curTimeScale = 1.0f;
		oldTimeScale = 1.0f;
		EndSlowmoS = TickS;
		return;
	}

	if (EndSlowmoS - TickS <= 0.0)
	{
		Toggles.CurTimescale = 1.0f;
		curTimeScale = 1.0f;
		oldTimeScale = 1.0f;
		EndSlowmoS = TickS;
		return;
	}

	if (EndSlowmoS - TickS > 0.0 && EndSlowmoS - TickS <= EndLen)
	{
		double diff = EndSlowmoS - TickS;
		Toggles.CurTimescale = max(1.0f * (1.0f - (float)(diff / EndLen)), curTimeScale);
		oldTimeScale = Toggles.CurTimescale;
		return;
	}

	if (TickS - StartTime <= StartLen &&  TickS - StartTime >= 0.0)
	{
		double diff = TickS - StartTime;
		Toggles.CurTimescale = max(oldTimeScale * (1.0f - (float)(diff / StartLen)),curTimeScale);
		oldTimeScale = Toggles.CurTimescale;
		return;
	}

	Toggles.CurTimescale = curTimeScale;
	oldTimeScale = curTimeScale;
}
