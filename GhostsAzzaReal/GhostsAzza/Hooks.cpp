#include "stdafx.h"

bool first = true;
bool LastIngame = false;





#define RegisterHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourAttach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())
#define RemoveHook(original, hook) (DetourTransactionBegin(), DetourUpdateThread(GetCurrentThread()), DetourDetach(reinterpret_cast<LPVOID*>(&original), reinterpret_cast<LPVOID>(hook)), DetourTransactionCommit())

std::vector<KillEntry> KillList;

extern bool IsTeamBased();


Vector3::Vector3(float _x, float _y, float _z) {
	this->vec[0] = _x;
	this->vec[1] = _y;
	this->vec[2] = _z;
}

Vector3::Vector3(const float * origin) {
	this->vec[0] = origin[0];
	this->vec[1] = origin[1];
	this->vec[2] = origin[2];
}

void Vector3::Add(float val) {
	this->vec[0] += val;
	this->vec[1] += val;
	this->vec[2] += val;
}
void Vector3::Add(Vector3 val) {
	this->vec[0] += val.vec[0];
	this->vec[1] += val.vec[1];
	this->vec[2] += val.vec[2];
}
void Vector3::Add(const float* val) {
	this->vec[0] += val[0];
	this->vec[1] += val[1];
	this->vec[2] += val[2];
}

void Vector3::Subtract(float val) {
	this->vec[0] -= val;
	this->vec[1] -= val;
	this->vec[2] -= val;
}
void Vector3::Subtract(Vector3 val) {
	this->vec[0] -= val.vec[0];
	this->vec[1] -= val.vec[1];
	this->vec[2] -= val.vec[2];
}
void Vector3::Subtract(const float* val) {
	this->vec[0] -= val[0];
	this->vec[1] -= val[1];
	this->vec[2] -= val[2];
}

void Vector3::Divide(float val) {
	this->vec[0] /= val;
	this->vec[1] /= val;
	this->vec[2] /= val;
}
void Vector3::Divide(Vector3 val) {
	this->vec[0] /= val.vec[0];
	this->vec[1] /= val.vec[1];
	this->vec[2] /= val.vec[2];
}
void Vector3::Divide(const float* val) {
	this->vec[0] /= val[0];
	this->vec[1] /= val[1];
	this->vec[2] /= val[2];
}

void Vector3::Multiply(float val) {
	this->vec[0] *= val;
	this->vec[1] *= val;
	this->vec[2] *= val;
}
void Vector3::Multiply(Vector3 val) {
	this->vec[0] *= val.vec[0];
	this->vec[1] *= val.vec[1];
	this->vec[2] *= val.vec[2];
}
void Vector3::Multiply(const float* val) {
	this->vec[0] *= val[0];
	this->vec[1] *= val[1];
	this->vec[2] *= val[2];
}


void Load()
{
	Engine.OpenConsole();

	Engine.Conbuf_AppendText("\n\n");

	Engine.Conbuf_AppendText("Sidaz's Host Tools\n\n");
	Engine.Conbuf_AppendText("[INS] - Host/Player Menu\n");
	Engine.Conbuf_AppendText("[DEL] - Mod/Bot Menus\n");
	Engine.Conbuf_AppendText("[F7]  - Radar Hack\n");

	Engine.Conbuf_AppendText("\n\n");

	first = false;
}

void ExplosiveBullets(int clientNum)
{

	//if (clientNum <= 18)
	{

		void* attackerent = Engine.GetEntity(clientNum);

		if ((!Engine.EntNumHasBool(clientNum, true, Toggles.EB_LimitWeapons) || Engine.HasValidWeapon(attackerent)))
		{

			/*uint64_t client = *(int64_t*)(0x14427A0E0 + (0x2E0 * clientNum) + 0x168);


			Vector3 forwardedAngles = Vector3(0, 0, 0);
			Vector3 angles = Vector3(Engine.PlayerCmd_GetAngles(clientNum)[0], Engine.PlayerCmd_GetAngles(clientNum)[1], Engine.PlayerCmd_GetAngles(clientNum)[2]);
			Vector3 getEye = Vector3(0, 0, 0);

			//Engine.Add_Ammo(client, *(int*)(client + 0x41C), 0, 999, 1);

			printf("Angles: %f, %f, %f\n", angles.vec[0], angles.vec[1], angles.vec[2]);

			Engine.AngleVectorss(angles.vec, forwardedAngles.vec, NULL, NULL);
			Engine.G_GetPlayerEyePosition(client, getEye.vec);
			forwardedAngles.Multiply(999999);

			printf("getEye: %f, %f, %f\n", getEye.vec[0], getEye.vec[1], getEye.vec[2]);

			Vector3 end = Vector3(Engine.Scr_BulletTrace(clientNum, getEye.vec, forwardedAngles.vec));

			printf("End: %f, %f, %f\n", end.vec[0], end.vec[1], end.vec[2]);*/

			uint64_t client = *(int64_t*)(0x000000014427A0E0 + (0x2F0 * clientNum) + 0x168);

			
			//void* ent = Engine.GetEntity(realclient);
			//void* localEnt = Engine.GetEntity(*Engine.LocalPlayer);

			Vector3 forwardedAngles = Vector3(0, 0, 0);
			Vector3 angles = Vector3(Engine.PlayerCmd_GetAngles(clientNum)[0], Engine.PlayerCmd_GetAngles(clientNum)[1], Engine.PlayerCmd_GetAngles(clientNum)[2]);
			Vector3 getEye = Vector3(0, 0, 0);

			//Engine.Add_Ammo(client, *(int*)(client + 0x41C), 0, 999, 1);

			Engine.AngleVectorss(angles.vec, forwardedAngles.vec, NULL, NULL);
			Engine.G_GetPlayerEyePosition(client, getEye.vec);
			forwardedAngles.Multiply(999999);


			Vector3 end = Vector3(Engine.Scr_BulletTrace(clientNum, getEye.vec, forwardedAngles.vec));

			for (int i = 0; i < 18; i++)
			{
				uint64_t tempEnt = Engine.Scr_GetEntity(i);
				uint64_t tempClient = *(uint64_t*)(tempEnt + 0x168);

				void* tempentfordamage = Engine.GetEntity(i);

				if (i != clientNum && !Toggles.EB_IGNORE[i])
				{
					float distance = Engine.GetDistance(end, Vector3(*(float*)(tempClient + 0x1C), *(float*)(tempClient + 0x20), *(float*)(tempClient + 0x24)));


					if (*(int*)(tempEnt + 0x1DC) > 0)
					{

						if (distance < Toggles.EBRADIUSplayer[clientNum])
						{
							int damageforhealth = tempEnt + 0x1DC;


							bool hs = Engine.GenHeadshot();

							//bool hm = Engine.GenHitmark(clientNum);

							if (Toggles.EB_HitMarkers[clientNum])
							{

								int returnnumber = Engine.returnnumber();


								if (returnnumber <= Toggles.Hitmarkchance[clientNum])
								{
									damageforhealth = 10;
								}

							}
							

							Vector dirVec = Vector(0, 0, 0);

							Vector posVec = Engine.GetBonePos(tempentfordamage, hs ? "j_head" : "j_spineupper");

							Vector aView = Engine.GetViewOrigin(attackerent);
							Engine.vectoangles(&(posVec - aView), &dirVec);

							


							

							
							

							{

								Engine.oG_Damage(tempentfordamage, attackerent, attackerent, &dirVec, &posVec, damageforhealth, 0, hs ? MOD_HEAD_SHOT : MOD_RIFLE_BULLET, 0, 0, hs ? HITLOC_HEAD : HITLOC_TORSO_UPR, 0, 0, 0);
							}


							break;
						}
					}
				}
			}
		}
	}
}
void hk_Scr_NotifyNum(int entnum, unsigned int classnum, void* string, unsigned int paramcount)
{
	
		//return;

	//printf("%s\n", Engine.GScr_AllocString(string));
	if (string == Engine.GScr_AllocString("weapon_fired") && Engine.EntNumHasBool(entnum, true, Toggles.EB))
	{
		void* attackerent = Engine.GetEntity(entnum);
		if (Engine.IsPlayer(attackerent))
		{

			{

				ExplosiveBullets(entnum);
			}
			

		}
		





	}
		
	

	/*if (string == Engine.GScr_AllocString("weapon_fired") && Engine.EntNumHasBool(entnum, true, Toggles.TA))
	{
		void* attackerent = Engine.GetEntity(entnum);
		if (Engine.IsPlayer(attackerent))
		{
			if (!Engine.EntNumHasBool(entnum, true, Toggles.TA_LimitWeapons) || Engine.HasValidWeapon(attackerent))
			{
				
				void* bestent = 0;
				float bestfov = Toggles.TA_FOV[entnum];
				if (Toggles.TA_FOV[entnum] == 180.0f)
					bestfov = 999.9f;

				for (int i = 0; i < 2048; i++)
				{
					if (i == entnum)
						continue;

					if (Engine.EntNumHasBool(i, true, Toggles.GodMode))
						continue;

					if (Engine.EntNumHasBool(i, true, Toggles.TA_IgnoreAim))
						continue;

					//Vec3 tag_eye = Engine.GetBonePos2(attackerent, "tag_eye");

					//Engine.AngleVectors(player[i].angles, vecout, NULL, NULL);
					//Engine.Scr_BulletTrace(entnum, tag_eye, );


					void* eent = Engine.GetEntity(i);
					if (Engine.EntIsEligible(attackerent, eent))
					{
						float fovx = Engine.CalculateFOVx(attackerent, eent);
						float fovy = Engine.CalculateFOVy(attackerent, eent);
						float fovz = Engine.CalculateFOVz(attackerent, eent);

						printf("fovz: %f\n", fovz);

						//fovz = 15.0f;
						if (fovx < bestfov && fovy < bestfov && fovz < bestfov)
						{
							bestent = eent;
							bestfov = fovy;
							
						}
					}
				}

				if (bestent)
				{
					KillEntry k;
					k.attacker = attackerent;
					k.victim = bestent;
					KillList.push_back(k);
				}
			}
		}
	}*/
		

	Engine.oScr_NotifyNum(entnum, classnum, string, paramcount);
}

void hk_VM_Resume(unsigned int time)
{
	//if (!Engine.InGame)
	Engine.oVM_Resume(time);


	//if (Engine.PlayerCmd_useButtonPressed(*Engine.LocalPlayer))
		//printf("usebuttonpressed!\n");



	for (int i = 0; i < KillList.size(); i++)
	{
		void* targent = KillList[i].victim;
		void* attackerent = KillList[i].attacker;
		bool hs = Engine.GenHeadshot();

		Vector dirVec = Vector(0, 0, 0);
		//SimHit hit;
		Vector posVec = Engine.GetBonePos(targent, hs ? "j_head" : "j_spineupper");
		//Engine.GenHit(targent, attackerent, &hit);
		Vector aView = Engine.GetViewOrigin(attackerent);
		Engine.vectoangles(&(posVec - aView), &dirVec);
		//Engine.oG_Damage(targent, attackerent, attackerent, &dirVec, &hit.Pos, 1000, 0, hit.MOD, 0, 0, hit.HITLOC, 0, 0, 0);

		Engine.oG_Damage(targent, attackerent, attackerent, &dirVec, &posVec, 1000, 0, hs ? MOD_HEAD_SHOT : MOD_RIFLE_BULLET, 0, 0, hs ? HITLOC_HEAD : HITLOC_TORSO_UPR, 0, 0, 0);
	}
	KillList.clear();

	for (int i = 0; i < Engine.slayList.size(); i++)
	{
		int num = Engine.slayList[i];
		void* ent = Engine.GetEntity(num);
		void* atkent = Engine.GetEntity(num);
		if (ent)
		{
			if (Engine.IsAlive(ent))
			{
				Vector dirVec(1, 1, 1);
				Engine.oG_Damage(ent, atkent, atkent, &dirVec, &dirVec, 1000, 0, MOD_HEAD_SHOT, 0, 0, HITLOC_HEAD, 0, 0, 0);
			}
		}
	}
	Engine.slayList.clear();

	Engine.GSC_CreateTestClient();

}


float nigger = 99999.9f;
//WeaponDef *bg_weaponDefs = (WeaponDef*)0x140844610;


//declares
#define NOP 0x90
//declares

#define getweaponslistitems 14038CA90 


/*void giveKillstreakWeapon(const char *weapon)
{
	weaponList = getWeaponsListItems();

	for each()
	{
		if (!isSubStr(item, "killstreak"))
			continue;

		if (self getCurrentWeapon() == item)
			continue;

		self takeWeapon(item);
	}

	DWORD_PTR weapon;
	bool isAlt;
	char wepname[128];

	G_GetWeaponForEntity(ent, &weapon, &isAlt);
	SimEngine::BG_GetWeaponName((void*)weapon, wepname, 127);


	giveWeapon(nigger, 0);
	setActionSlot(4, "weapon", weapon);
}

int _Buttons(int client)
{
	gentity_s * thisPlayer = getEntity(client);
	return thisPlayer->clientData->buttons;
*/



playerState_s *playerstate = (playerState_s*)0x1474AF348;


void setweaponstate(int clientnum)
{

	*(int *)((&playerstate->weapState[0].weaponState) + (clientnum * 0x3A68)) = 0;
	*(int *)((&playerstate->weapState[1].weaponState) + (clientnum * 0x3A68)) = 0;
	*(int *)((&playerstate->weapState[2].weaponState) + (clientnum * 0x3A68)) = 0;


}


void __fastcall hk_g_radiusdamage(const float *origin, int *inflictor, int *attacker, float fInnerDamage, float fOuterDamage, float radius, float coneAngleCos, float *coneDirection, int *ignore, meansOfDeath_t mod, Weapon weapon, bool isAlternate)
{

	printf("origin: %f inflictor: %x attacker: %x finnerdamage: %f fouterdamage: %f radius: %f coneAngleCos: %f coneDirection: %f ignore: %i mod: %i weapon: %x isalternate: %i", origin, inflictor, attacker, fInnerDamage, fOuterDamage, radius, coneAngleCos, ignore, mod, weapon , isAlternate);

	Engine.og_radiusdamage(origin, inflictor, attacker, fInnerDamage,  fOuterDamage,  radius,  coneAngleCos,  coneDirection,  ignore,  mod,  weapon,  isAlternate);

}


void GiveEB(int clientNum)
{
	void* a = *(void**)(0x14427C0E0 + 0x158 + 0X2E0 * clientNum);
	if (a)
	{
		*(int*)(((char*)a) + 0xE14 + 4 * (34 >> 5)) = 0xFF; // 0x24
	}
}

typedef void(__fastcall* tStartMapt)(__int64 localClientNum, const char *map, bool mapIsPreloaded);
tStartMapt StartMapt = (tStartMapt)0x140470170;

void hk_EndFrame()
{
	Engine.oEndFrame();

	//if (first)
	//oad();

	// (Engine.InGame() != LastIngame)
//
//if (!Engine.InGame())
//	Toggles.Init();
	//*(int*)(pm + 0x2B4) = 0;
	//*(int*)(pm + 0x2D0) = 0;
//LastIngame = Engine.InGame();
//




	//for (;;)
	//{
		//if (GetDvar_Bool("cl_ingame"))
		//{
		//	for (int client = 0; client < 18; client++)
		//	{
			//	if (_Buttons(client) & 0x4)
			//	{
					//Open Menu For The Client or whatever
			//	}
		//	}
		//}
	//}

	if (Utils::CheckKeyState(VK_F5, 1)) {
		//for (int i = 0; i < 18; i++)
			//GiveEB(i);
		Engine.Cbuf_AddText(0, "xblive_privatematch 1;onlinegame 0;party_teambased 1;xpartygo;onlinegame 1;xblive_privatematch 0;set scr_dm_score_kill 999999;set scr_war_score_kill 999999");
		//printf("okkokeoekeok\n");
			//Engine.Cbuf_AddText(*Engine.LocalPlayer, "disconnect");
			//StartMapt(0, "mp_chasm", false);
		
	}
	


	//for (int i = 0; i < 18; ++i)
	//	setweaponstate(i);

	//printf("weaponstatenigger: %i", level_locals->clients.ps.weapState->weaponState);

	//Engine.party_maxteamdiff->current.integer = 8;
	//0x1408254D4

	//nop_(0x140240016, );


	//1417352E0 +

	// nop 140240016
	//140240018 
	//000 F3 0F 10 81 40 0A 00 00                       movss   xmm0, dword ptr [rcx+0A40h] ; Move Scalar Single-FP

	//printf("%f\n", bg_weaponDefs->player_meleeRange);
	//bg_weaponDefs->player_meleeRange = 990.0f;

	if (!Engine.InGame())
	{
		if (Toggles.SetMaxPlayers)
		{
			//Engine.party_maxplayers->current.integer = Toggles.MaxPlayers;
			//Engine.party_teambased->current.enabled = IsTeamBased();
			//printf("%s\n", Engine.party_teambased->current.enabled ? "True" : "False");
		}
	}
	else
	{
		//Vector go = Engine.GetBonePos(Engine.GetEntity(1), "j_head");
		//Engine.CalculateFOVHit(Engine.GetEntity(0), go);

		Engine.SwitchUfo();
		Slowmo.Update();
	}

}

void __fastcall hk_G_Damage(void *targent, void *inflictorent, void *attackerrnt, const Vector *dir, const Vector *point, int damage, int dFlags, int mod, void* iweapon, bool isAlternate, hitLocation_t hitLoc, unsigned int modelIndex, void* partName, int timeOffset)
{
	if (Engine.EntHasBool(targent, true, Toggles.GodMode))
	{
		return;

		//Engine.GameSendServerCommand(0, 2, "")
	}


	


		//return;

//	printf("etype: %i\n", *(int*)((DWORD_PTR)targent + 4));
//	return *(int*)((DWORD_PTR)targent + 4) == 1 || *(int*)((DWORD_PTR)ent + 4) == 5;

	Engine.oG_Damage(targent, inflictorent, attackerrnt, dir, point, damage, dFlags, mod, iweapon, isAlternate, hitLoc, modelIndex, partName, timeOffset);
}

void __fastcall hk_player_die(void* targent, void* inflictorent, void* attackerent, int damage, int meansOfDeath, void* iWeapon, bool isAlternate, const float *vDir, hitLocation_t hitLoc, int psTimeOffset)
{
	if (targent && attackerent)
	{
		if (Engine.IsPlayer(targent) && Engine.IsPlayer(attackerent))
		{
			if (!Engine.IsSameTeam(targent, attackerent))
			{
				if (hitLoc == hitLocation_t::HITLOC_HEAD || hitLoc == hitLocation_t::HITLOC_HELMET)
				{
					if (Toggles.HeadshotSlowmo)
					{
						Slowmo.AddSlowmo(2.0f, 0.15f);
						//Engine.Com_SetSlowMotion(1.0f, 0.2f, 0.5f);
					}
				}
			}
		}
	}
	return Engine.oplayer_die(targent, inflictorent, attackerent, damage, meansOfDeath, iWeapon, isAlternate, vDir, hitLoc, psTimeOffset);
}

signed __int64 __fastcall hk_CL_MouseEvent(unsigned int a1, unsigned int a2, int a3, int a4)
{
	if (Toggles.HostMenu)
		return 0;
	return Engine.oCL_MouseEvent(a1, a2, a3, a4);
}

void __fastcall hk_ClientSpawn(void *ent, const Vector *spawn_origin, const Vector *spawn_angles)
{
	Engine.oClientSpawn(ent, spawn_origin, spawn_angles);
	//Engine.FixTeams(ent);
	if (Engine.IsPlayer(ent))
	{
		int num = *(int*)ent;
		if (Toggles.SpawnSaved[num] && Toggles.SavedPositions[num] != Vector(0, 0, 0))
			Engine.TeleportPlayer(ent, &Toggles.SavedPositions[num]);
	}
}

char* __fastcall hk_GetName()
{
	if (!Toggles.ChangeName)
		return Engine.oGetName();

	return (char*)Toggles.NameToChange.c_str();
}

float __fastcall hk_GetSoundTimescale()
{
	if (Toggles.CurTimescale != 1.0f)
		return Toggles.CurTimescale;
	return Engine.oGetSoundTimescale();
}

void getequippedoffhand(int a1, int a2, int a3)
{
	printf("PlayerCmd_giveweapon(%i, %i, %i)\n", a1, a2, a3);

	//a2 = 122;

	Engine.ogetequippedoffhand(a1, a2, a3);
}

bool __fastcall hk_Bot_BotSystemEnabled()
{
	return Toggles.Bot_Think;
}




typedef void*(__fastcall* ttGScr_AllocString)(const char* string);
ttGScr_AllocString oGScr_AllocString;

void hk_allocstring(const char* string)
{
	//printf("%s\n", string);


	oGScr_AllocString(string);
}
//14038AF80 = player_switchtoweapon


typedef int(__cdecl* tswitchtoweapon)(int gentity, bool immediate);
tswitchtoweapon oswitchtoweapon;

int playecmd_switchtoweapon(int gentity, bool immediate)
{
	immediate = true;

	int returnswitch = oswitchtoweapon(gentity, immediate);


	printf("%i\n", immediate);

	//oswitchtoweapon(gentity, immediate);
	return returnswitch;
}

struct Material {
	const char* szMaterialName;
};

typedef void(__cdecl* tPM_BeginWeaponChange)(playerState_s *pm, int newweapon, bool isNewAlternate, bool quick, unsigned int *holdrand);
tPM_BeginWeaponChange oPM_BeginWeaponChange;

typedef void(__cdecl* tPM_Weapon_CheckForSprint)(playerState_s *pm);
tPM_Weapon_CheckForSprint oPM_Weapon_CheckForSprint;

typedef void(__cdecl* tPM_Weapon)(playerState_s *pm, int pml);
tPM_Weapon oPM_Weapon;

typedef void(__cdecl* tR_AddCmdDrawStretchPic)(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, float* color, Material* material);
tR_AddCmdDrawStretchPic oR_AddCmdDrawStretchPic;

typedef void(__cdecl* tDRAWROTATEDPIC)(LPVOID screenmatrix, float x, float y, float w, float h, float angle, float* color, Material* shader);
tDRAWROTATEDPIC oDRAWROTATEDPIC;


typedef void(__cdecl* tPM_Weapon_BeginWeaponRaise)(int *pm, int anim, unsigned int time, float aim, int altSwitch, PlayerHandIndex hand);
tPM_Weapon_BeginWeaponRaise oPM_Weapon_BeginWeaponRaise;

void PM_BeginWeaponChange(playerState_s *pm, int newweapon, bool isNewAlternate, bool quick, unsigned int *holdrand)
{
	//quick = true;


	*(int*)(pm + 0x2B4) = 0;
	*(int*)(pm + 0x2D0) = 0;
	*(int*)(pm + 0x2B0) = 0;
	*(int*)(pm + 0x2B0) = 0;
	*(int*)(pm + 0x2BC) = 0;
	*(int*)(pm + 0x2CC) = 0;
	*(int*)(pm + 0x2D8) = 0;
	*(int*)(pm + 0x2AC) = 0;
	//2C8


	


	//isNewAlternate = true;

	oPM_BeginWeaponChange(pm, newweapon, isNewAlternate, quick, holdrand);
}

void PM_Weapon_CheckForSprint(playerState_s *pm)
{

	*(int*)(pm + 0x2B4) = 0;
	*(int*)(pm + 0x2D0) = 0;
	*(int*)(pm + 0x2B0) = 0;
	*(int*)(pm + 0x2B0) = 0;
	*(int*)(pm + 0x2BC) = 0;
	*(int*)(pm + 0x2CC) = 0;
	*(int*)(pm + 0x2D8) = 0;
	*(int*)(pm + 0x2AC) = 0;


	oPM_Weapon_CheckForSprint(pm);
}

void PM_Weapon(playerState_s *pm, int pml)
{


	*(int*)(pm + 0x2B4) = 0;
	*(int*)(pm + 0x2D0) = 0;
	*(int*)(pm + 0x2B0) = 0;
	*(int*)(pm + 0x2B0) = 0;
	*(int*)(pm + 0x2BC) = 0;
	*(int*)(pm + 0x2CC) = 0;
	*(int*)(pm + 0x2D8) = 0;
	*(int*)(pm + 0x2AC) = 0;

	printf("PM_weapon(pm: 0x%x, pml: 0x%x)\n", pm, pml);


	//1402307A0
	oPM_Weapon(pm, pml);
}


void hkR_AddCmdDrawStretchPic(uint64_t r3, uint64_t r4, uint64_t r5, uint64_t r6, uint64_t r7, uint64_t r8, uint64_t r9, uint64_t r10, float* color, Material* material)
{

	printf("Material:%s\n", material->szMaterialName);



	oR_AddCmdDrawStretchPic(r3, r4, r5, r6, r7, r8, r9, r10, color, material);
}

void HKDRAWROTATEDPIC(LPVOID screenmatrix, float x, float y, float w, float h, float angle, float* color, Material* shader)
{

	printf("Material:%s\n", shader->szMaterialName);



	oDRAWROTATEDPIC(screenmatrix, x, y, w, h, angle, color, shader);
}

//27 18

void PM_Weapon_BeginWeaponRaise(int *pm, int anim, unsigned int time, float aim, int altSwitch, PlayerHandIndex hand)
{
	time = 10;


	printf("anim: %i \n", anim);

	anim = 18;

	oPM_Weapon_BeginWeaponRaise(pm, anim, time, aim, altSwitch, hand);
}

//void(*VM_Notify_Stub)(unsigned int notifyListOwnerId, int stringValue, VariableValue* top) = (void(*)(unsigned int, int, VariableValue*))0x000000014043D9B0;

struct VariableStackBuffer
{
	const char* pos;
	unsigned __int16 size;
	unsigned __int16 bufLen;
	unsigned __int16 localId;
	char time;
	char buf[1];
};

union VariableUnion
{
	int intValue;
	unsigned int uintValue;
	float floatValue;
	unsigned int stringValue;
	const float* vectorValue;
	const char* codePosValue;
	unsigned int pointerValue;
	VariableStackBuffer* stackValue;
	unsigned int entityOffset;
};

struct VariableValue
{
	VariableUnion u;
	int type;
};

typedef void(__cdecl* tVM_Notify)(unsigned int notifyListOwnerId, int stringValue, VariableValue* top);
tVM_Notify oVM_Notify;


void Multiply(Vec3 val) {

	Vec3 vec;
	vec[0] *= val[0];
	vec[1] *= val[1];
	vec[2] *= val[2];
}

void(*VM_Notify_Stub)(unsigned int notifyListOwnerId, int stringValue, VariableValue* top) = (void(*)(unsigned int, int, VariableValue*))0x000000014043D9B0;





void VM_Notify(unsigned int notifyListOwnerId, int stringValue, VariableValue* top)
{
	const char* notify = Engine.SL_ConvertToStringg(stringValue);

	if (!strcmp(notify, "weapon_fired"))
	{
		

		
		
		//ExplosiveBullets(Engine.Scr_GetSelf(notifyListOwnerId));
		
	}

	oVM_Notify(notifyListOwnerId, stringValue, top);
}

typedef const char*(__cdecl* tSV_BotGetRandomName)();
tSV_BotGetRandomName oSV_BotGetRandomName;

const char* selectedname = "napan";

const char* SV_BotGetRandomName()
{
	return selectedname;
}

typedef void(__cdecl* tClientScr_SetScore)(int* gclient);
tClientScr_SetScore oClientScr_SetScore;


typedef void(__fastcall* tStartMap)(__int64 localClientNum, const char *map, bool mapIsPreloaded);
tStartMap StartMap;
typedef void(__fastcall* tStartMap2)(__int64 localClientNum);
tStartMap2 StartMap2;
typedef void(__fastcall* tStartMap3)(__int64 localClientNum);
tStartMap3 StartMap3;

typedef void(__cdecl* idkfunction_t)(const char* menu);
idkfunction_t idkfunction;
void startmap(__int64 localClientNum, const char *map, bool mapIsPreloaded)
{

	//printf("gclient: 0x%p , 0x%p", gclient, (int)((DWORD_PTR)gclient + 13520));

	printf("%i , %s , %i", localClientNum, map, mapIsPreloaded);

	StartMap(localClientNum, map, mapIsPreloaded);
}

void ClientScr_SetScore(int *gclient)
{

	printf("gclient: 0x%p , 0x%p", gclient, (int)((DWORD_PTR)gclient + 13520));

	oClientScr_SetScore(gclient);
}


void startmap2(__int64 localclientnum)
{

	printf("startmap2: %i\n", localclientnum);

	StartMap2(localclientnum);
}


void idkfunctionn(const char* menu)
{

	

	if (!strcmp(menu, "MENU_WAITING_FOR_MORE_PLAYERS_TEAMS"))
		menu = "MENU_MAKING_TEAMS";
	 if (strcmp(menu, "MENU_NUM_VOTES"))
		 printf("Menu: %s\n", menu);
	
	

	

	idkfunction(menu);
}

typedef void(__cdecl* Jump_PushOffLadder)(int* a1, int* a3);
Jump_PushOffLadder oJump_PushOffLadder;


void hk_Jump_PushOffLadder(int* a1, int* a2)
{

	


	oJump_PushOffLadder(a1, a2);


	*(float *)(a1 + 48) = *(float *)(a1 + 48) * 20.0;
}

//*(float *)(a1 + 48) = *(float *)(a1 + 48) * 0.75;
void SimHooks::Hook()
{
	
	//Load();
	//if (Engine.initialized)
	{

		//RegisterHook(VM_Notify_Stub, VM_Notify);
		
		MH_CreateHook((void*)0x140601AA0, (void*)hk_EndFrame, (LPVOID*)&Engine.oEndFrame);
		MH_EnableHook((void*)0x140601AA0);


		//MH_CreateHook((void*)0x140213350, (void*)hk_Jump_PushOffLadder, (LPVOID*)&oJump_PushOffLadder);
		//MH_EnableHook((void*)0x140213350);
		//MH_CreateHook((void*)0x140470170, (void*)startmap, (LPVOID*)&StartMap);
		//MH_EnableHook((void*)0x140470170);

		//MH_CreateHook((void*)0x1404BA080, (void*)startmap2, (LPVOID*)&StartMap2);
		//MH_EnableHook((void*)0x1404BA080);

		//MH_CreateHook((void*)0x140460B50, (void*)SV_BotGetRandomName, (LPVOID*)&oSV_BotGetRandomName);
		//MH_EnableHook((void*)0x140460B50);

	//	MH_CreateHook((void*)0x140600BE0, (void*)hkR_AddCmdDrawStretchPic, (LPVOID*)&oR_AddCmdDrawStretchPic);
	//	MH_EnableHook((void*)0x140600BE0);
		//MH_CreateHook((void*)0X140231500, (void*)PM_Weapon_BeginWeaponRaise, (LPVOID*)&oPM_Weapon_BeginWeaponRaise);
		//MH_EnableHook((void*)0X140231500);

		//MH_CreateHook((void*)0x000000014043D9B0, (void*)VM_Notify, (LPVOID*)&oVM_Notify);
		//MH_EnableHook((void*)0x000000014043D9B0);

		//MH_CreateHook((void*)0x140386F80, (void*)ClientScr_SetScore, (LPVOID*)&oClientScr_SetScore);
		//MH_EnableHook((void*)0x140386F80);


	//	MH_CreateHook((void*)0x140600BE0, (void*)hkR_AddCmdDrawStretchPic, (LPVOID*)&oR_AddCmdDrawStretchPic);
	//	MH_EnableHook((void*)0x140600BE0);

	//	MH_CreateHook((void*)0x140261270, (void*)HKDRAWROTATEDPIC, (LPVOID*)&oDRAWROTATEDPIC);
	//	MH_EnableHook((void*)0x140261270);

		
		//MH_CreateHook((void*)0x1402307A0, (void*)PM_Weapon, (LPVOID*)&oPM_Weapon);
		//MH_EnableHook((void*)0x1402307A0);

		//MH_CreateHook((void*)0x14038F770, (void*)playecmd_switchtoweapon, (LPVOID*)&oswitchtoweapon);
		//MH_EnableHook((void*)0x14038F770);

		//MH_CreateHook((void*)0x140395D10, (void*)hk_g_radiusdamage, (LPVOID*)&Engine.og_radiusdamage);
		//MH_EnableHook((void*)0x140395D10);
		//MH_CreateHook((void*)0x14022E9D0, (void*)PM_Weapon_CheckForSprint, (LPVOID*)&oPM_Weapon_CheckForSprint);
		//MH_EnableHook((void*)0x14022E9D0);

		//MH_CreateHook((void*)0x140232B80, (void*)PM_BeginWeaponChange, (LPVOID*)&oPM_BeginWeaponChange);
		//MH_EnableHook((void*)0x140232B80);

		MH_CreateHook((void*)0x1404397E0, (void*)hk_Scr_NotifyNum, (LPVOID*)&Engine.oScr_NotifyNum);
		MH_EnableHook((void*)0x1404397E0);

		//MH_CreateHook((void*)0x1404397E0, (void*)hk_Scr_NotifyNum, (LPVOID*)&Engine.oScr_NotifyNum);
		//MH_EnableHook((void*)0x1404397E0);


		MH_CreateHook((void*)0x1403C38F0, (void*)hk_allocstring, (LPVOID*)&oGScr_AllocString);
		MH_EnableHook((void*)0x1403C38F0);

		MH_CreateHook((void*)0x14043DE30, (void*)hk_VM_Resume, (LPVOID*)&Engine.oVM_Resume);
		MH_EnableHook((void*)0x14043DE30);

		MH_CreateHook((void*)0x140394DF0, (void*)hk_G_Damage, (LPVOID*)&Engine.oG_Damage);
		MH_EnableHook((void*)0x140394DF0);

		MH_CreateHook((void*)0x1402C12A0, (void*)hk_CL_MouseEvent, (LPVOID*)&Engine.oCL_MouseEvent);
		MH_EnableHook((void*)0x1402C12A0);

		MH_CreateHook((void*)0x140387B20, (void*)hk_ClientSpawn, (LPVOID*)&Engine.oClientSpawn);
		MH_EnableHook((void*)0x140387B20);

		MH_CreateHook((void*)0x1404FDAA0, (void*)hk_GetName, (LPVOID*)&Engine.oGetName);
		MH_EnableHook((void*)0x1404FDAA0);

		MH_CreateHook((void*)0x140413860, (void*)hk_GetSoundTimescale, (LPVOID*)&Engine.oGetSoundTimescale);
		MH_EnableHook((void*)0x140413860);

		//MH_CreateHook((void*)0x140396920, (void*)hk_player_die, (LPVOID*)&Engine.oplayer_die);
		//MH_EnableHook((void*)0x140396920);

		MH_CreateHook((void*)0x140217020, (void*)hk_Bot_BotSystemEnabled, (LPVOID*)&Engine.oBot_BotSystemEnabled);
		MH_EnableHook((void*)0x140217020);

		printf("functions hooked\n");





	}
}
