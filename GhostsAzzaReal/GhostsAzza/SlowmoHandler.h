#pragma once

class SlowmoHandler
{
private:
	DWORD64 EndSlowmo = 0;
	float curTimeScale = 1.0f, curLength = 0.0f, oldTimeScale = 1.0f;
public:
	void AddSlowmo(float length, float timeScale);
	void Update();
};

extern SlowmoHandler Slowmo;