#include "stdafx.h"

const std::string weapons[] = { "iw6_l115a3_mp" ,"iw6_svu_mp", "iw6_usr_mp", "iw6_vks_mp", "iw6_mk14_mp", "iw6_gm6_mp" };

char* BoneNames[] = 
{ 
	"j_head",
	"j_shoulder_ri","j_shoulder_le",
	"j_elbow_ri","j_elbow_le",
	"j_knee_ri","j_knee_le",
	"j_ankle_ri","j_ankle_le",
	"j_spineupper","j_spinelower",
	"j_wrist_ri","j_wrist_le",
	"j_mainroot" 
};

hitLocation_t HitLocs[] =
{
	HITLOC_HEAD,
	HITLOC_R_ARM_UPR,HITLOC_L_ARM_UPR,
	HITLOC_R_ARM_LWR,HITLOC_L_ARM_LWR,
	HITLOC_R_LEG_UPR,HITLOC_L_LEG_UPR,
	HITLOC_R_LEG_LWR,HITLOC_L_LEG_LWR,
	HITLOC_TORSO_UPR,HITLOC_TORSO_LWR,
	HITLOC_R_HAND,HITLOC_L_HAND,
	HITLOC_TORSO_LWR
};

bool SimEngine::HasValidWeapon(void* ent)
{
	DWORD_PTR weapon;
	bool isAlt;
	char wepname[128];

	G_GetWeaponForEntity(ent, &weapon, &isAlt);
	BG_GetWeaponName((void*)weapon, wepname, 127);

	for (int i = 0; i < ARRAYSIZE(weapons); i++)
	{
		if (strstr(wepname, weapons[i].c_str()))
			return true;
	}
	return false;
}


void SimEngine::GenHit(void* targent, void* attackerent, SimHit* hit)
{
	Vector BestBonePos = GetBonePos(targent, "j_head");
	float maxFov = CalculateFOVHit(attackerent, BestBonePos);
	int boneIndx = 0;

	for (int i = 1; i < ARRAYSIZE(BoneNames); i++)
	{
		Vector BonePos = GetBonePos(targent, BoneNames[i]);
		float curFov = CalculateFOVHit(attackerent, BonePos);
		if (curFov < maxFov)
		{
			BestBonePos = BonePos;
			maxFov = curFov;
			boneIndx = i;
		}
	}

	hit->Pos = BestBonePos;
	hit->MOD = boneIndx == 0 ? MOD_HEAD_SHOT : MOD_RIFLE_BULLET;
	hit->HITLOC = HitLocs[boneIndx];
}
