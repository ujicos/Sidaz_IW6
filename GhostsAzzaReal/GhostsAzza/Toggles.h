#pragma once
class SimToggles
{
public:
	bool HostMenu = false;
	bool ModMenu = false;

	bool DLCUnlock = false;

	bool UFO[18];
	bool OldUFO[18];

	bool EB[18];
	bool EB_LimitWeapons[18];
	bool EB_IGNORE[18];
	bool EB_HitMarkers[18];

	bool SetTeam[18];

	bool patchshit;

	int Hitmarkchance[18];

	float EBRADIUS = 150;
	int time = 10;
	bool GodMode[18];

	float EBRADIUSplayer[18];
	
	Vector SavedPositions[18];
	bool SpawnSaved[18];

	int CurGameType = 0;
	int CurMap = 0;

	void HandleKeys(WPARAM param);
	void Init();

	int MaxPlayers = 12;
	bool SetMaxPlayers = false;

	bool ChangeName = false;

	float CurTimescale = 1.0f;
	float oldTimeScale = 1.0f;

	bool HeadshotSlowmo = false;

	bool Bot_Changename = false;
	bool Bot_NoKick = false;
	bool depatch = false;
	bool depatchele = false;
	bool Bot_Think = false;

	int Team_Selected = 0;

	std::string BotName = "";

	std::string NameToChange = "";
};

extern SimToggles Toggles;