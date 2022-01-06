#pragma once

#define OFFSET 0x1405030E0
#define STARTMATCHADDY 0x1402EAD70
#define BALANCETEAMSADDY 0x4D73B0
#define FINDVARADDY 0x5BCE00
//#define OpenMenu 0x1404BA210



typedef enum
{
	DVAR_FLAG_NONE = 0x0,				//no flags
	DVAR_FLAG_SAVED = 0x1,				//saves in config_mp.cfg for clients
	DVAR_FLAG_LATCHED = 0x2,			//no changing apart from initial value (although it might apply on a map reload, I think)
	DVAR_FLAG_CHEAT = 0x4,				//cheat
	DVAR_FLAG_REPLICATED = 0x8,			//on change, this is sent to all clients (if you are host)
	DVAR_FLAG_UNKNOWN10 = 0x10,			//unknown
	DVAR_FLAG_UNKNOWN20 = 0x20,			//unknown
	DVAR_FLAG_UNKNOWN40 = 0x40,			//unknown
	DVAR_FLAG_UNKNOWN80 = 0x80,			//unknown
	DVAR_FLAG_USERCREATED = 0x100,		//a 'set' type command created it
	DVAR_FLAG_USERINFO = 0x200,			//userinfo?
	DVAR_FLAG_SERVERINFO = 0x400,		//in the getstatus oob
	DVAR_FLAG_WRITEPROTECTED = 0x800,	//write protected
	DVAR_FLAG_UNKNOWN1000 = 0x1000,		//unknown
	DVAR_FLAG_READONLY = 0x2000,		//read only (same as 0x800?)
	DVAR_FLAG_UNKNOWN4000 = 0x4000,		//unknown
	DVAR_FLAG_UNKNOWN8000 = 0x8000,		//unknown
	DVAR_FLAG_UNKNOWN10000 = 0x10000,	//unknown
	DVAR_FLAG_DEDISAVED = 0x1000000,	//unknown
	DVAR_FLAG_NONEXISTENT = 0xFFFFFFFF	//no such dvar
} dvar_flag;

enum DvarSetSource
{
	DVAR_SOURCE_INTERNAL = 0,
	DVAR_SOURCE_EXTERNAL = 1,
	DVAR_SOURCE_SCRIPT = 2
};
union DvarLimits {
	struct
	{
		int stringCount;
		char * * strings;
	} enumeration;
	struct
	{
		int min;
		int max;
	} integer;
	struct
	{
		float min;
		float max;
	} decimal;
};

union DvarValue {
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	float value;
	float vector[4];
	char * string;
	BYTE color[4];
};

typedef enum DvarType : char
{
	DVAR_TYPE_BOOL = 0x00,
	DVAR_TYPE_FLOAT = 0x01,
	DVAR_TYPE_VEC2 = 0x02,
	DVAR_TYPE_VEC3 = 0x03,
	DVAR_TYPE_VEC4 = 0x04,
	DVAR_TYPE_INT = 0x05,
	DVAR_TYPE_ENUM = 0x06,
	DVAR_TYPE_STRING = 0x07,
	DVAR_TYPE_COLOR = 0x08,
	DVAR_TYPE_DEVTWEAK = 0x09
} DvarType;

enum perksEnum
{
	PERK_ACCURACY = 0x0,
	PERK_FASTRELOAD = 0x1,
	PERK_RATEOFFIRE = 0x2,
	PERK_EXTRABREATH = 0x3,
	PERK_LONGERSPRINT = 0x4,
	PERK_DETECTEXPLOSIVE = 0x5,
	PERK_EXPOSEENEMY = 0x6,
	PERK_EXTRAAMMO = 0x7,
	PERK_TWOPRIMARIES = 0x8,
	PERK_ARMORVEST = 0x9,
	PERK_FRAGGRENADE = 0xA,
	PERK_SPECIALGRENADE = 0xB,
	PERK_EXTENDEDMAGS = 0xC,
	PERK_LIGHTWEIGHT = 0xD,
	PERK_MARATHON = 0xE,
	PERK_QUICKDRAW = 0xF,
	PERK_IMPROVEDEXTRABREATH = 0x10,
	PERK_FASTSPRINTRECOVERY = 0x11,
	PERK_EXTENDEDMELEE = 0x12,
	PERK_FASTOFFHAND = 0x13,
	PERK_STALKER = 0x14,
	PERK_HOLDBREATHWHILEADS = 0x15,
	PERK_LONGERRANGE = 0x16,
	PERK_FASTERMELEE = 0x17,
	PERK_REDUCEDSWAY = 0x18,
	PERK_JAMRADAR = 0x19,
	PERK_EXTRABP = 0x1A,
	PERK_GRENADEDEATH = 0x1B,
	PERK_PISTOLDEATH = 0x1C,
	PERK_QUIETMOVE = 0x1D,
	PERK_PARABOLIC = 0x1E,
	PERK_BULLETDMG = 0x1F,
	PERK_SPRINTRELOAD = 0x20,
	PERK_NOT_USED = 0x21,
	PERK_EXPLOSIVEBULLETS = 0x22,
	PERK_SCAVENGER = 0x23,
	PERK_COLDBLOODED = 0x24,
	PERK_BLINDEYE = 0x25,
	PERK_NOPLAYERTARGET = 0x26,
	PERK_HEARTBREAKER = 0x27,
	PERK_SELECTIVEHEARING = 0x28,
	PERK_FASTSNIPE = 0x29,
	PERK_SPYGAME = 0x2A,
	PERK_AUTOMANTLE = 0x2B,
	PERK_QUICKSWAP = 0x2C,
	PERK_LOWPROFILE = 0x2D,
	PERK_HEARTBREAKER_PRO = 0x2E,
	PERK_THROWBACK = 0x2F,
	PERK_RADAR_ISREDBLIP = 0x30,
	PERK_RADAR_ISREDARROW = 0x31,
	PERK_RADAR_ISJUGGERNAUT = 0x32,
	PERK_SILENTKILL = 0x33,
	PERK_NOSCOPEOUTLINE = 0x34,
	PERK_COUNT = 0x35,
	PERK_UNKNOWN = 0x35,
};

enum meansOfDeath_t
{
	MOD_UNKNOWN = 0x0,
	MOD_PISTOL_BULLET = 0x1,
	MOD_RIFLE_BULLET = 0x2,
	MOD_EXPLOSIVE_BULLET = 0x3,
	MOD_GRENADE = 0x4,
	MOD_GRENADE_SPLASH = 0x5,
	MOD_PROJECTILE = 0x6,
	MOD_PROJECTILE_SPLASH = 0x7,
	MOD_MELEE = 0x8,
	MOD_HEAD_SHOT = 0x9,
	MOD_MELEE_DOG = 0xA,
	MOD_MELEE_ALIEN = 0xB,
	MOD_CRUSH = 0xC,
	MOD_FALLING = 0xD,
	MOD_SUICIDE = 0xE,
	MOD_TRIGGER_HURT = 0xF,
	MOD_EXPLOSIVE = 0x10,
	MOD_IMPACT = 0x11,
	MOD_NUM = 0x12,
};
enum hitLocation_t
{
	HITLOC_NONE = 0x0,
	HITLOC_HELMET = 0x1,
	HITLOC_HEAD = 0x2,
	HITLOC_NECK = 0x3,
	HITLOC_TORSO_UPR = 0x4,
	HITLOC_TORSO_LWR = 0x5,
	HITLOC_R_ARM_UPR = 0x6,
	HITLOC_L_ARM_UPR = 0x7,
	HITLOC_R_ARM_LWR = 0x8,
	HITLOC_L_ARM_LWR = 0x9,
	HITLOC_R_HAND = 0xA,
	HITLOC_L_HAND = 0xB,
	HITLOC_R_LEG_UPR = 0xC,
	HITLOC_L_LEG_UPR = 0xD,
	HITLOC_R_LEG_LWR = 0xE,
	HITLOC_L_LEG_LWR = 0xF,
	HITLOC_R_FOOT = 0x10,
	HITLOC_L_FOOT = 0x11,
	HITLOC_GUN = 0x12,
	HITLOC_SHIELD = 0x13,
	HITLOC_ARMOR = 0x14,
	HITLOC_SOFT = 0x15,
	HITLOC_NUM = 0x16,
};



typedef struct dvar_t //dvar struct
{
	char * name;
	dvar_flag flags;
	DvarType type;
	bool modified;

	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarLimits domain;
	dvar_t * next;
} dvar_t;


//my dvar api

template <class Value>
inline void WriteDvarPointer(DWORD pointer, DWORD pointerofs, Value value)
{
	DWORD dwPointer = *(DWORD*)pointer;
	*(Value*)(dwPointer + pointerofs) = value;
}

template <class Value>
inline Value ReadDvarPointer(DWORD pointer, DWORD pointerofs)
{
	DWORD dwPointer = *(DWORD*)pointer;
	return *(Value*)(dwPointer + pointerofs);
}

template <class Value>
inline Value* ReadGetDvarPointer(DWORD pointer, DWORD pointerofs)
{
	DWORD dwPointer = *(DWORD*)pointer;
	return (Value*)(dwPointer + pointerofs);
}

class RGBA
{
public:
	RGBA() { r = g = b = a = 0.0f; }
	RGBA(float R, float G, float B, float A = 1.0f) { r = R; g = G; b = B; a = A; }
	RGBA(const RGBA &v) { r = v.r; g = v.g; b = v.b; a = v.a; }

	void operator = (const float *farray) { r = farray[0]; g = farray[1]; b = farray[2]; a = farray[3]; }
	void operator = (const float &val) { r = g = b = a = val; }
	float& operator [] (unsigned int element) { switch (element) { case 1: return g; case 2: return b; case 3: return a; default: return r; } }

	static RGBA FromRGBA(int R, int G, int B, int A = 255)
	{
		RGBA col;
		col.r = R / 255.0f;
		col.g = G / 255.0f;
		col.b = B / 255.0f;
		col.a = A / 255.0f;
		return col;
	}

	float r, g, b, a;
};



void GiveEB(int clientNum)
{
	void* a = *(void**)(0x14427A0E0 + 0X168 + 0X2F0 * clientNum);
	if (a)
	{
		*(int*)(((char*)a) + 0xE14 + 4 * (34 >> 5)) = 0x04; // 0x24
	}
}
void DelEB(int clientNum)
{
	void* a = *(void**)(0x14427A0E0 + 0X168 + 0X2F0 * clientNum);
	if (a)
		*(INT*)(((char*)a) + 0xE14 + 4 * (34 >> 5)) = 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00;
}
 
void GivePerk(int clientnum, perksEnum perk)
{
	void* a = *(void**)(0x14427A0E0 + 0X168 + 0X2F0 * clientnum);
	if (a)
	{
		BYTE* nigs = (BYTE*)((char*)a + 0xE36);
		nigs[(int)perk] = 0x00;
	}
}
void RemovePerk(int clientnum, perksEnum perk)
{
	void* a = *(void**)(0x14427A0E0 + 0X168 + 0X2F0 * clientnum);
	if (a)
	{
		BYTE* nigs = (BYTE*)((char*)a + 0xE36);
		nigs[(int)perk] = 0x00;
	}
}

void WriteBytes(DWORD address, char* bytes, size_t length)
{
	DWORD a, b;
	VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &a);
	for (size_t i = 0; i < length; i++)
	{
		*(char*)(address + i) = bytes[i];
	}
	VirtualProtect((void*)address, length, a, &b);
}