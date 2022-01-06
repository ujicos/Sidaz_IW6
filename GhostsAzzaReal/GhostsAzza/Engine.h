#pragma once





class SimEngine
{
public:

	
	
		
	typedef void(__cdecl* t_Dvar_SetString)(const char *dvar, const char *value);
	t_Dvar_SetString Dvar_SetString = (t_Dvar_SetString)0x1404F08E0;

	bool initialized;
	typedef dvar_t* (__cdecl* tFindDvar)(const char* dvarname);
	tFindDvar FindDvar = (tFindDvar)0x1404ECB60;

	typedef int (__cdecl* tDvar_GetInt)(const char* dvarname);
	tDvar_GetInt Dvar_GetInt = (tDvar_GetInt)0x00000001404ECD90;

	typedef const char* (__cdecl* tDvar_GetString)(const char* dvarname);
	tDvar_GetString Dvar_GetString = (tDvar_GetString)0x1404ECDD0;

	typedef float (__cdecl* tDvar_GetFloat)(const char* dvarname);
	tDvar_GetFloat Dvar_GetFloat = (tDvar_GetFloat)0x1404ECCF0;

	typedef void(__fastcall* tGameSendServerCommand)(int clientNum, int type, const char *text);
	tGameSendServerCommand GameSendServerCommand = (tGameSendServerCommand)0x1404758C0;
	//tGameSendServerCommand oGameSendServerCommand;

	typedef int(__cdecl* tOpenConsole)();
	tOpenConsole OpenConsole = (tOpenConsole)0x140503130;

	typedef signed __int64(__fastcall* tNetConstStrings_SV_GetNetworkDvarIndex)(dvar_t* dvar, DWORD *outdvarindex);
	tNetConstStrings_SV_GetNetworkDvarIndex NetConstStrings_SV_GetNetworkDvarIndex = (tNetConstStrings_SV_GetNetworkDvarIndex)0x1403E9BC0;

	typedef void*(__fastcall* tGScr_AllocString)(const char* string);
	tGScr_AllocString GScr_AllocString = (tGScr_AllocString)0x1403C38F0;

	typedef char *(__fastcall *tG_GetDObj)(int clientNum);
	tG_GetDObj G_GetDObj = (tG_GetDObj)0x140416490;

	typedef signed __int64(__fastcall* tG_DObjGetWorldTagPos)(void *entity, void* stringref, Vector* posRet);
	tG_DObjGetWorldTagPos G_DObjGetWorldTagPos = (tG_DObjGetWorldTagPos)0x1403D6D60;

	typedef void(__fastcall* tvectoangles)(Vector* vec, Vector* retAngles);
	tvectoangles vectoangles = (tvectoangles)0x1404E36A0;

	typedef __int64(__fastcall* tScr_GetType)(int entNum);
	tScr_GetType Scr_GetType = (tScr_GetType)0x140439280;

	typedef __int64(__fastcall* tG_GetEntityTeam)(void* entity);
	tG_GetEntityTeam G_GetEntityTeam = (tG_GetEntityTeam)0x1403D82C0;

	typedef void(__fastcall* tAnglesToAxis)(const Vector *angles, float(*axis)[3]);
	tAnglesToAxis AnglesToAxis = (tAnglesToAxis)0x1404E3BA0;

	typedef void(__fastcall* tG_GetPlayerViewOrigin)(void *ps, Vector *origin);
	tG_GetPlayerViewOrigin G_GetPlayerViewOrigin = (tG_GetPlayerViewOrigin)0x140388790;

	typedef void*(__fastcall* tSV_GetPlayerstateForClientNum)(int num);
	tSV_GetPlayerstateForClientNum SV_GetPlayerstateForClientNum = (tSV_GetPlayerstateForClientNum)0x140475A10;

	typedef void(__fastcall* tG_GetWeaponForEntity)(void *ent, void *retweapon, bool *retisAlternate);
	tG_GetWeaponForEntity G_GetWeaponForEntity = (tG_GetWeaponForEntity)0x140395A20;
	
	typedef int(__cdecl* tGetWeapIndexForName)(const char* weapname);
	tGetWeapIndexForName Getweaponindexforname = (tGetWeapIndexForName)0x1403DA060; // getting the index of the weapon 

	typedef char *(__fastcall* tBG_GetWeaponName)(void* weapon, char *output, unsigned int maxStringLen);
	tBG_GetWeaponName BG_GetWeaponName = (tBG_GetWeaponName)0x140239350;

	typedef void(__fastcall* tConbuf_AppendText)(const char *pMsg);
	tConbuf_AppendText Conbuf_AppendText = (tConbuf_AppendText)0x1405028C0;
	
	typedef int (__cdecl* t_giveplayerweapon)(int64_t ps, int weapon, int dualWield, int startInAltMode, int usedBefore); // dont need the actual structure of playerstate
	t_giveplayerweapon G_GivePlayerWeapon = (t_giveplayerweapon)0x1403DA5E0; 

	typedef void(__fastcall* tAngleVectors)(const Vector *angles, Vector *forward, Vector *right, Vector *up);
	tAngleVectors AngleVectors = (tAngleVectors)0x140230A10;

	typedef signed __int64(__fastcall* tCL_GetClientName)(int localClientNum, int index, char *buf, int size);
	tCL_GetClientName CL_GetClientName = (tCL_GetClientName)0x1402CF770;

	typedef void(__fastcall* tSV_GameDropClient)(int clientNum, const char *reason);
	tSV_GameDropClient SV_GameDropClient = (tSV_GameDropClient)0x140475890;

	typedef void( __fastcall* tG_SetOrigin)(void *ent, const Vector *origin);
	tG_SetOrigin G_SetOrigin = (tG_SetOrigin)0x1403D8860;

	typedef void(__fastcall* tSetClientOrigin)(void *ent, const Vector *origin, int teleport);
	tSetClientOrigin SetClientOrigin = (tSetClientOrigin)0x140388810;

	typedef __int64(__fastcall* tG_GetOrigin)(int localClientNum, int entIndex, Vector *outPosition);
	tG_GetOrigin G_GetOrigin = (tG_GetOrigin)0x1403D8390;

	typedef void(__fastcall* tCbuf_AddText)(int localClientNum, const char *text);
	tCbuf_AddText Cbuf_AddText = (tCbuf_AddText)0x1403F6B50;

	typedef void *(__fastcall* tSV_AddTestClient)(char* wtf, const int team, const int index, scr_entref_t team_owners_client);
	tSV_AddTestClient SV_AddTestClient = (tSV_AddTestClient)0x140470920;

	typedef void*  (__fastcall* tSV_SpawnTestClient)(void *ent);
	tSV_SpawnTestClient SV_SpawnTestClient = (tSV_SpawnTestClient)0x1404740A0;

	typedef void(__fastcall* tScr_AddEntity)(void *ent);
	tScr_AddEntity Scr_AddEntity = (tScr_AddEntity)0x1403D3480;

	typedef void(__fastcall* tScr_AddInt)(int inn);
	tScr_AddInt Scr_AddInt = (tScr_AddInt)0x1404380F0;

	typedef void(__fastcall* tScr_ClearOutParams)();
	tScr_ClearOutParams Scr_ClearOutParams = (tScr_ClearOutParams)0x140438600;

	typedef void(__fastcall* tGScr_AddTestClient)();
	tGScr_AddTestClient GScr_AddTestClient = (tGScr_AddTestClient)0x1403CBD50;

	typedef void(__fastcall* tScr_AddString)(const char *value);
	tScr_AddString Scr_AddString = (tScr_AddString)0x1404381D0;

	typedef void*(__fastcall* tSV_AddBot)(const char *bot_name, unsigned int head, unsigned int body, unsigned int helmet);
	tSV_AddBot SV_AddBot = (tSV_AddBot)0x140470B70;
	//tSV_AddBot oSV_AddBot;

	typedef void*(__fastcall* tGScr_AddBot)();
	tGScr_AddBot GScr_AddBot = (tGScr_AddBot)0x1403CBC80;

	typedef void(__fastcall* tCom_SetSlowMotion)(const float startTimescale, const float endTimescale, const int deltaMsec);
	tCom_SetSlowMotion Com_SetSlowMotion = (tCom_SetSlowMotion)0x1404158C0;
	
	typedef char *(__fastcall* tSL_ConvertToString)(void* stringValue);
	tSL_ConvertToString SL_ConvertToString = (tSL_ConvertToString)0x1404317F0;

	typedef void(__fastcall* tSV_FastRestart)(int localClientNum);
	tSV_FastRestart SV_FastRestart = (tSV_FastRestart)0x14046F440;

	typedef int(__fastcall* tSV_GetAssignedTeam)(int clientnum);
	tSV_GetAssignedTeam SV_GetAssignedTeam = (tSV_GetAssignedTeam)0x140479BD0;

	typedef void(__fastcall* tCalculateRanks)();
	tCalculateRanks CalculateRanks = (tCalculateRanks)0x14039E260;

	typedef void(__fastcall* tClientStateTeamChanged)(int clientNum);
	tClientStateTeamChanged ClientStateTeamChanged = (tClientStateTeamChanged)0x1403880D0;

	typedef void(__cdecl *tG_Damage)(void *targent, void *inflictorent, void *attackerrnt, const Vector *dir, const Vector *point, int damage, int dFlags, int mod, void* iweapon, bool isAlternate, hitLocation_t hitLoc, unsigned int modelIndex, void* partName, int timeOffset);
	//tG_Damage G_Damage = (tG_Damage)0x140394DF0;
	tG_Damage oG_Damage;

	typedef void(__fastcall *tG_Damagee)(uint64_t* targent, uint64_t* inflictorent, uint64_t* attackerrnt, const Vector *dir, const Vector *point, int damage, int dFlags, int mod, void* iweapon, bool isAlternate, hitLocation_t hitLoc, unsigned int modelIndex, void* partName, int timeOffset);
	//tG_Damage G_Damage = (tG_Damage)0x140394DF0;
	tG_Damagee oG_Damagee;

	typedef void(__cdecl *tVM_Resume)(unsigned int timeId);
	tVM_Resume oVM_Resume;

	typedef void(__cdecl* tScr_NotifyNum)(int entnum, unsigned int classnum, void* string, unsigned int paramcount);
	tScr_NotifyNum oScr_NotifyNum;

	typedef void(__cdecl* tEndFrame)();
	tEndFrame oEndFrame;

	typedef void(__fastcall* tg_radiusdamage)(const float *origin, int *inflictor, int *attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float *coneDirection, int *ignore, meansOfDeath_t mod, Weapon weapon, bool isAlternate);
	tg_radiusdamage og_radiusdamage;

	typedef signed __int64(__fastcall* tCL_MouseEvent)(unsigned int a1, unsigned int a2, int a3, int a4);
	tCL_MouseEvent oCL_MouseEvent;

	typedef void(__fastcall* tClientSpawn)(void *ent, const Vector *spawn_origin, const Vector *spawn_angles);
	tClientSpawn oClientSpawn;

	typedef char*(__fastcall* tGetName)();
	tGetName oGetName;

	typedef float(__fastcall* tGetSoundTimescale)();
	tGetSoundTimescale oGetSoundTimescale;

	typedef char*(__fastcall* tSV_BotGetRandomName)();
	tSV_BotGetRandomName oSV_BotGetRandomName;

	typedef void(__fastcall* tplayer_die)(void* selfent, void* inflictorent, void* attackerent, int damage, int meansOfDeath, void* iWeapon, bool isAlternate, const float *vDir, hitLocation_t hitLoc, int psTimeOffset);
	tplayer_die oplayer_die;

	typedef bool(__fastcall* tBot_BotSystemEnabled)();
	tBot_BotSystemEnabled oBot_BotSystemEnabled;

	typedef bool(__fastcall* tgetequippedoffhand)(int a1, int a2, int a3);
	tgetequippedoffhand ogetequippedoffhand;

	typedef void(__fastcall* tCG_LocationalTrace)(trace_t *results, const float *start, const float *end, int passEntityNum, int contentmask);
	tCG_LocationalTrace CG_LocationalTrace = (tCG_LocationalTrace)0x14039F810;

	dvar_t* cl_ingame = FindDvar("cl_ingame");
	dvar_t* g_gametype = FindDvar("g_gametype");
	dvar_t* ui_gametype = FindDvar("ui_gametype");
	dvar_t* party_minplayers = FindDvar("party_minplayers");
	dvar_t* party_maxTeamDiff = FindDvar("party_maxTeamDiff");
	//dvar
	dvar_t* party_maxplayers = FindDvar("party_maxplayers");
	dvar_t* party_maxteamdiff = FindDvar("party_maxteamdiff");
	dvar_t* party_teambased = FindDvar("party_teambased");
	dvar_t* bg_compassShowEnemies = FindDvar("bg_compassShowEnemies");
	dvar_t* sv_maxclients = FindDvar("sv_maxclients");
	dvar_t* scr_sd_timelimit = FindDvar("scr_sd_timelimit");


	float* timescale = (float*)0x1445CEF84;
	float* com_timescale = (float*)0x1409EB228;

	std::vector<int> slayList;
	std::vector<SimTestClient> TestClientAdd;
	
	int* LocalPlayer = (int*)0x14176ED7C;
	//int* LocalPlayer2 = (int*)0x141771F60;

	int* GetEntMoveType(int entnum)
	{
		void* ent = GetEntity(entnum);

		if (!ent)
			return 0;
		if (!IsPlayer(ent))
			return 0;
		if (!IsAlive(ent))
			return 0;

		void* ps = SV_GetPlayerstateForClientNum(entnum);
		if (!ps)
			return 0;

		return (int*)((DWORD_PTR)ps + 4);
	}

	int* GetEntNoclip(int entnum)
	{
		void* ent = GetEntity(entnum);

		if (!ent)
			return 0;
		if (!IsPlayer(ent))
			return 0;
		if (!IsAlive(ent))
			return 0;

		return (int*)((DWORD_PTR)0x1444505C0 + (0x3A68 * entnum));
	}

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
		snprintf(buf, 128, "q %i %s", dIndx, dvarValueString);
		GameSendServerCommand(clientnum, 1, buf);
	}

	void GSSC_Message(int clientnum, const char* message)
	{
		char buf[258];
		snprintf(buf, 258, "c \"%s\"", message);
		GameSendServerCommand(clientnum, 1, buf);
	}
	
	void TeleportPlayer(void* ent, Vector *pos)
	{
		G_SetOrigin(ent, pos);
		SetClientOrigin(ent,pos,0);
	}

	bool InGame()
	{
		return cl_ingame->current.enabled;
	}

	void SwitchUfo()
	{
		for (int i = 0; i < 18; i++)
		{
			bool Changed = Toggles.UFO[i] != Toggles.OldUFO[i];
			if (Toggles.UFO[i])
			{
				int* uf = GetEntNoclip(i);
				if (uf)
				{
					if (*uf != 2)
						*uf = 2;
				}
			}
			if (Changed)
			{
				if (!Toggles.UFO[i])
				{
					int* uf = GetEntNoclip(i);
					if (uf)
						*uf = 0;
				}
				*(int*)((DWORD_PTR)GetEntity(i) + 476) = 99;
			}
				
		}
		memcpy(Toggles.OldUFO, Toggles.UFO, sizeof(bool) * 18);
	}


	bool GenHeadshot()
	{
		const int perc = 20;
		return (rand() % 100) <= perc;
	}

	bool GenHitmark(int clientnum)
	{
		int perc = Toggles.Hitmarkchance[clientnum];
		return (rand() % 100) <= perc; // 1 op 5 als het kleiner is dan perc return true
	}

	int returnnumber()
	{


		return (rand() % 10);
	}

	void* GetEntity(int entnum)
	{
		return (void*)(0x14427A0E0 + (752 * entnum));
	}

	int* GetClient(int entnum)
	{
		return (int*)(0x14427A0E0 + (752 * entnum) + 0x168);
	}

	int GetHealth(void* ent)
	{
		return *(int*)((DWORD_PTR)ent + 476);
	}

	bool IsPlayer(void* ent)
	{
		return *(int*)((DWORD_PTR)ent + 4) == 1 || *(int*)((DWORD_PTR)ent + 4) == 5;
	}

	bool IsAlive(void* ent)
	{
		return GetHealth(ent) > 0;
	}

	Vector GetEntityViewAngles(void* ent)
	{

	 //ent + 45;
		//return *(Vector*)((DWORD_PTR)ent + 45 + 388);
		return *(Vector*)((DWORD_PTR)ent + 332);
	}


	const char* (*SL_ConvertToStringg)(unsigned int stringValue) = (const char* (*)(unsigned int))0x00000001404317F0;
	int(*Scr_GetSelf)(unsigned int notifyOwnerId) = (int(*)(unsigned int))0x0000000140436F10;
	char* (*va)(const char* fmt, ...) = (char*(*)(const char *, ...))0x00000001404F79D0;
	void(*SV_GameSendServerCommand)(int clientNum, int reliable, const char* command) = (void(*)(int, int, const char*))0x00000001404758C0;
//	int(*CL_GetClientName)(int localClientNum, int index, char* buf, int size) = (int(*)(int, int, char*, int))0x00000001402CF770;
	void(*Cmd_RegisterNotification)(int clientNum, const char* commandString, const char* notifyString) = (void(*)(int, const char*, const char*))0x00000001403F7A90;
	void(*G_LocationalTrace)(trace_t* results, const float* start, const float* end, int passEntityNum, int contentmask) = (void(*)(trace_t *, const float*, const float*, int, int))0x000000014039F810;
	void(*AngleVectorss)(const float* angles, float* forward, float* right, float* up) = (void(*)(const float*, float*, float*, float*))0x00000001404E39E0;
	void(*G_GetPlayerEyePosition)(int64_t ps, float* origin) = (void(*)(int64_t, float*))0x0000000140388710;

	void(*Add_Ammo)(int64_t ps, int weapon, bool isAlternate, int count, int fillClip) = (void(*)(int64_t, int, bool, int, int))0x0000000140399E50;

	void(*G_Damageee)(__int64 targ, __int64 inflictor, __int64 attacker, const float* dir, const float* point, int damage, int dFlags, int mod, int iweapon, bool isAlternate, hitLocation_t hitLoc, unsigned int modelIndex, unsigned int partName, int timeOffset) = (void(*)(__int64, __int64, __int64, const float*, const float*, int, int, int, int, bool, hitLocation_t, unsigned int, unsigned int, int))0x0000000140394DF0;
	void(*G_RadiusDamage)(const float* origin, uint64_t inflictor, uint64_t attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float* coneDirection, uint64_t ignore, meansOfDeath_t mod, int weapon, bool isAlternate) = (void(*)(const float*, uint64_t, uint64_t, float, float, float, float, float*, uint64_t, meansOfDeath_t, int, bool))0x0000000140395D30;

	__int64 Scr_GetEntity(int client) {
		return (0x000000014427A0E0 + (client * 0x2F0));
	}

	__int64 Scr_GetEntityClient(int client) {
		return (0x000000014427A0E0 + (client * 0x2F0)+ 0x168);
	}

	float GetDistance(Vector3 point1, Vector3 point2) {
		return sqrtf((point1.vec[0] - point2.vec[0]) * (point1.vec[0] - point2.vec[0]) + (point1.vec[1] - point2.vec[1]) * (point1.vec[1] - point2.vec[1]) + (point1.vec[2] - point2.vec[2]) * (point1.vec[2] - point2.vec[2]));
	}

	const float * PlayerCmd_GetAngles(int clientNum) {
		int64_t client = *(int64_t*)(0x000000014427A0E0 + (0x2F0 * clientNum) + 0x168);
		float angles[3] = { *(float*)(client + 0x184), *(float*)(client + 0x188), *(float*)(client + 0x18C) };
		return angles;
	}

	const float* Scr_BulletTrace(int clientNum, const float * start, const float * end) {
		trace_t trace;
		float bullet[3];
		G_LocationalTrace(&trace, start, end, clientNum, 0x280E831);
		bullet[0] = (end[0] - start[0]) * trace.fraction + start[0];
		bullet[1] = (end[1] - start[1]) * trace.fraction + start[1];
		bullet[2] = (end[2] - start[2]) * trace.fraction + start[2];
		return bullet;
	}

	Vec3 GetBonePos2(void* ent, const char* bone)
	{
		Vector ret = Vector(0, 0, 0);
		void* boneStr = GScr_AllocString(bone);
		G_DObjGetWorldTagPos(ent, boneStr, &ret);
		return ret;
	}

	Vector GetBonePos(void* ent, const char* bone)
	{
		Vector ret = Vector(0, 0, 0);
		void* boneStr = GScr_AllocString(bone);
		G_DObjGetWorldTagPos(ent, boneStr, &ret);
		return ret;
	}

	Vector GetViewOrigin(void* ent)
	{
		Vector ret(0, 0, 0);
		void* ps = SV_GetPlayerstateForClientNum(*(int*)ent);
		G_GetPlayerViewOrigin(ps, &ret);
		return ret;
	}

	bool HasValidWeapon(void* ent);

	void NormalizeAngles(Vector &ang)
	{
		if (ang.x < 0)
			ang.x += 360.0f;
		if (ang.y < 0)
			ang.y += 360.0f;
	}


	Vec3 Scr_BulletTrace(int Entnum, Vec3 start, Vec3 end)
	{
		trace_t trace;
		Vec3 bullet;
		CG_LocationalTrace(&trace, start, end, Entnum, 0x2806831);
		bullet.x = start.x + (end.x - start.x) * trace.fraction;
		bullet.y = (end.y - start.y) * trace.fraction + start.y;
		bullet.z = trace.fraction * (end.z - start.z) + start.z;
		return bullet;
	}

	float CalculateFOVx(void* ent, void* targ)
	{
		Vector VicOrigin = GetBonePos(targ, "j_spineupper");
		Vector AimAngles = Vector(0, 0, 0);

		Vector attackerOrigin = GetViewOrigin(ent);
		Vector attackerAng = GetEntityViewAngles(ent);

		vectoangles(&(VicOrigin - attackerOrigin), &AimAngles);

		NormalizeAngles(attackerAng);
		NormalizeAngles(AimAngles);

		Vector delta = AimAngles - attackerAng;
		NormalizeAngles(delta);


		float fov = delta.x;
		if (fov > 180.0f)
		{
			fov -= 180.0f;
			if (fov > 180.0f)
				fov = 180.0f;

			fov = 180.0f - fov;
		}
		return fov;
	}

	float CalculateFOVy(void* ent, void* targ)
	{
		Vector VicOrigin = GetBonePos(targ, "j_spineupper");
		Vector AimAngles = Vector(0, 0, 0);

		Vector attackerOrigin = GetViewOrigin(ent);
		Vector attackerAng = GetEntityViewAngles(ent);

		vectoangles(&(VicOrigin - attackerOrigin), &AimAngles);

		NormalizeAngles(attackerAng);
		NormalizeAngles(AimAngles);

		Vector delta = AimAngles - attackerAng;
		NormalizeAngles(delta);

		float fov = delta.y;
		if (fov > 180.0f)
		{
			fov -= 180.0f;
			if (fov > 180.0f)
				fov = 180.0f;

			fov = 180.0f - fov;
		}
		return fov;
	}

	float CalculateFOVz(void* ent, void* targ)
	{
		Vector VicOrigin = GetBonePos(targ, "j_spineupper");
		Vector AimAngles = Vector(0, 0, 0);

		Vector attackerOrigin = GetViewOrigin(ent);
		Vector attackerAng = GetEntityViewAngles(ent);

		vectoangles(&(VicOrigin - attackerOrigin), &AimAngles);

		NormalizeAngles(attackerAng);
		NormalizeAngles(AimAngles);

		Vector delta = AimAngles - attackerAng;
		NormalizeAngles(delta);

		float fov = delta.z;
		if (fov > 180.0f)
		{
			fov -= 180.0f;
			if (fov > 180.0f)
				fov = 180.0f;

			fov = 180.0f - fov;
		}
		return fov;
	}

	float CalculateFOVHit(void* ent, Vector tagpos)
	{
		
		Vector VicOrigin = tagpos;
		Vector AimAngles = Vector(0, 0, 0);

		Vector attackerOrigin = GetViewOrigin(ent);
		Vector attackerAng = GetEntityViewAngles(ent);

		vectoangles(&(VicOrigin - attackerOrigin), &AimAngles);

		//NormalizeAngles(attackerAng);
		//NormalizeAngles(AimAngles);

		
		Vector delta = AimAngles - attackerAng;
		//NormalizeAngles(delta);

		float fov = delta.x;
		if (fov > 180.0f)
		{
			fov -= 180.0f;
			if (fov > 180.0f)
				fov = 180.0;

			fov = 180.0f - fov;
		}
		
		return fov;
		
	}

	bool IsSameTeam(void* ent1, void* ent2)
	{
		if (ent1 == ent2)
			return true;

		if (!strcmp(g_gametype->current.string, "dm"))
			return false;

		return G_GetEntityTeam(ent1) == G_GetEntityTeam(ent2);
	}


	bool EntIsEligible(void* curent, void* targent)
	{
		return *(int*)((DWORD_PTR)targent + 4) == 1 || *(int*)((DWORD_PTR)targent + 4) == 18 && !IsSameTeam(curent, targent) && IsAlive(targent);
	}

	bool EntNumHasBool(int entnum, bool bol, bool* boolarray)
	{
		if (entnum < 0 || entnum >= 18)
			return false;
		return boolarray[entnum] == bol;
	}

	bool EntHasBool(void* ent, bool bol, bool* boolarray)
	{
		return EntNumHasBool(*(int*)ent, bol, boolarray);
	}

	bool NameTaken(char* name)
	{
		for (int i = 0; i < 18; i++)
		{
			if (IsPlayer(GetEntity(i)))
			{
				char namebuf[128];
				CL_GetClientName(*LocalPlayer, i, namebuf, 127);
				if (namebuf[0] != 0)
				{
					if (!strcmp(name, namebuf))
						return true;
				}
			}
		}
		return false;
	}

	void CreateTestClient(int team)
	{
		scr_entref_t owner;
		owner.classnum = 0;
		owner.entnum = *LocalPlayer;

		SimTestClient d;
		d.owner = owner;

		if (Toggles.Bot_Changename && !Toggles.BotName.empty() && Toggles.BotName != "")
			d.name = Toggles.BotName;

		d.team = team;
		TestClientAdd.push_back(d);
	}

	const char* textArray[7] = { "Cake", "Toast", "Butter", "Jelly" , "KeplerIsDogshit" ,"Minx2box" , "FalkOnlyScripts" };

	void GSC_CreateTestClient()
	{
		for (int i = 0; i < TestClientAdd.size(); i++)
		{
			SimTestClient a = TestClientAdd[i];
			void* ent = 0;
			char nig = 0;

			if (Toggles.Bot_Changename && !a.name.empty() && a.name != "")
				ent = SV_AddTestClient((char*)Toggles.BotName.c_str(), a.team, 0, a.owner);
			else
				ent = SV_AddTestClient(&nig, a.team, 0, a.owner);

			if (ent)
			{
				void* ret = SV_SpawnTestClient(ent);

				int RandIndex = rand() % 7;

				
				

				strcpy((char*)(0x144450344 + (*(int*)ent * 0x3A68)), textArray[RandIndex]);
				if (!ret)
				{
					SV_GameDropClient(*(int*)ent, "");
					GSSC_Message(*LocalPlayer, "^1Failed to spawn bot");
				}
			}
			else
				GSSC_Message(*LocalPlayer, "^1Failed to create bot");

		}
		TestClientAdd.clear();
	}

	void SetTeam(void* ent, int Team)
	{
		DWORD_PTR client = *(DWORD_PTR*)((DWORD_PTR)ent + 360);
		if (client) // client
		{
			*(int*)(client + 13304) = Team;
			ClientStateTeamChanged(*(int*)ent);
			CalculateRanks();
		}
	}

	void FixTeams(void* ent)
	{
		if (!strcmp(g_gametype->current.string, "dm"))
			return;

		if (ent && Toggles.SetTeam[*(int*)ent])
		{
			if (IsPlayer(ent))
			{
				if (!G_GetEntityTeam(ent))
				{
					printf("[%i] Assigned: %i\n", *(int*)ent, SV_GetAssignedTeam(*(int*)ent));

					int hostteam = SV_GetAssignedTeam(*LocalPlayer);

					SetTeam(ent,hostteam);
				}
			}
		}
	}


	void GenHit(void* targent, void* attackerent, SimHit* hit);
};

extern SimEngine Engine;