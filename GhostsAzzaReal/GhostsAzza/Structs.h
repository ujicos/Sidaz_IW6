#pragma once
typedef float Vec;
typedef Vec Vec2[2];

class Vec3
{
public:
	inline Vec3(void) { }
	inline Vec3(float X, float Y, float Z) { x = X; y = Y; z = Z; }
	inline Vec3(double X, double Y, double Z) { x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vec3(int X, int Y, int Z) { x = (float)X; y = (float)Y; z = (float)Z; }
	inline Vec3(const Vec3& v) { x = v.x; y = v.y; z = v.z; }
	inline Vec3(float rgfl[3]) { x = rgfl[0]; y = rgfl[1]; z = rgfl[2]; }
	inline Vec3 operator-(void) const { return Vec3(-x, -y, -z); }
	inline int operator==(const Vec3& v) const { return x == v.x && y == v.y && z == v.z; }
	inline int operator!=(const Vec3& v) const { return !(*this == v); }
	inline Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	inline Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	inline Vec3 operator*(float fl) const { return Vec3(x*fl, y*fl, z*fl); }
	inline float Vec3::operator*(const Vec3& other) const { return x * other.x + y * other.y + z * other.z; }
	inline Vec3 operator/(float fl) const { return Vec3(x / fl, y / fl, z / fl); }
	void operator += (const Vec3& add) { x += add.x; y += add.y; z += add.z; }
	void operator -= (const Vec3& sub) { x -= sub.x; y -= sub.y; z -= sub.z; }
	void operator *= (const float mul) { x *= mul; y *= mul; z *= mul; }
	void operator /= (const float mul) { x /= mul; y /= mul; z /= mul; }
	inline float Length(void) const { return (float)sqrt(x*x + y * y + z * z); }
	operator float *() { return &x; }
	operator const float *() const { return &x; }
	inline Vec3 CrossProduct(const Vec3 & other) { return{ y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x }; }
	float x, y, z;
};

struct Vector3 {
	float vec[3];

	Vector3(float _x, float _y, float _z);
	Vector3(const float* origin);

	void Add(float val);
	void Add(Vector3 val);
	void Add(const float* val);

	void Subtract(float val);
	void Subtract(Vector3 val);
	void Subtract(const float* val);

	void Divide(float val);
	void Divide(Vector3 val);
	void Divide(const float* val);

	void Multiply(float val);
	void Multiply(Vector3 val);
	void Multiply(const float* val);
};








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

struct Refdef
{
	int  x;
	int  y;
	int	 width;
	int	 height;
	float tanHalfFovX;
	float tanHalfFovY;
	Vector viewOrg;
};

struct KillEntry
{
	void* attacker;
	void* victim;
};

enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0x0,
	TRACE_HITTYPE_ENTITY = 0x1,
	TRACE_HITTYPE_DYNENT_MODEL = 0x2,
	TRACE_HITTYPE_DYNENT_BRUSH = 0x3,
	TRACE_HITTYPE_GLASS = 0x4,
};

struct trace_t
{
	float fraction;
	Vector surfaceDirection;
	int surfaceFlags;
	int contents;
	TraceHitType hitType;
	unsigned __int16 hitId;
	unsigned __int16 modelIndex;
	__int16 partName;
	unsigned __int16 partGroup;
	bool allsolid;
	bool startsolid;
	bool walkable;
	bool getPenetration;
	bool removePitchAndRollRotations;
};

struct traceBounds
{
	float midPoint[3];
	float halfSize[3];
};

struct scr_entref_t
{
	unsigned __int16 entnum;
	unsigned __int16 classnum;
};

struct SimHit
{
	Vector Pos;
	meansOfDeath_t MOD;
	hitLocation_t HITLOC;
};

struct SimTestClient
{
	std::string name;
	scr_entref_t owner;
	int team;
};

struct $9704E9D6F23D6A5E526351953F37E26F
{
	unsigned __int32 weaponIdx : 8;
	unsigned __int32 weaponVariation : 6;
	unsigned __int32 weaponScopes : 3;
	unsigned __int32 weaponUnderBarrels : 2;
	unsigned __int32 weaponOthers : 7;
	unsigned __int32 scopeVariation : 6;
};

union Weapon
{
	$9704E9D6F23D6A5E526351953F37E26F __s0;
	unsigned int data;
};


struct PlayerVehicleState
{
	int entity;
	int flags;
	int targetEntity;
	float origin[3];
	float angles[3];
	float velocity[3];
	float angVelocity[3];
	float tilt[2];
	float tiltVelocity[2];
	float gunAngles[2];
	unsigned int splineId;
	unsigned int splineNodeIndex;
	float splineLambda;
	float corridorSpeeds[2];
};


struct playerEvents_t
{
	int eventSequence;
	//	EntityEvent events[4];
	int oldEventSequence;
	int timeADSCameUp;
};

struct EntityEvent
{
	int eventType;
	int eventParm;
};

enum ViewLockTypes
{
	PLAYERVIEWLOCK_NONE = 0x0,
	PLAYERVIEWLOCK_FULL = 0x1,
	PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
	PLAYERVIEWLOCKCOUNT = 0x3,
};

struct SprintState_s
{
	int sprintButtonUpRequired;
	int sprintDelay;
	int lastSprintStart;
	int lastSprintEnd;
	int sprintStartMaxLength;
};

/* 1359 */
struct compressedAnimData_s
{
	int flags;
	int animRate;
	int distanceIn2D;
	int distanceOut2D;
	int distanceInZ;
	int distanceOutZ;
	int endScriptAnimTableIndex;
};

/* 1360 */
struct MantleState
{
	float yaw;
	int startPitch;
	int transIndex;
	int flags;
	int startTime;
	float startPosition[3];
	compressedAnimData_s compressedAnimData;
};


struct SlideState
{
	int flags;
	int noFricTime;
};


struct PlayerActiveWeaponState
{
	int weapAnim;
	int weaponTime;
	int weaponDelay;
	int weaponRestrictKickTime;
	int weaponState;
	int weapHandFlags;
	unsigned int weaponShotCount;
};

struct PlayerEquippedWeaponState
{
	bool usedBefore;
	bool dualWielding;
	bool inAltMode;
	bool needsRechamber[2];
	int zoomLevelIndex;
	bool thermalEnabled;
	bool hybridScope;
};


enum OffhandClass
{
	OFFHAND_CLASS_NONE = 0x0,
	OFFHAND_CLASS_FRAG_GRENADE = 0x1,
	OFFHAND_CLASS_SMOKE_GRENADE = 0x2,
	OFFHAND_CLASS_FLASH_GRENADE = 0x3,
	OFFHAND_CLASS_THROWINGKNIFE = 0x4,
	OFFHAND_CLASS_OTHER = 0x5,
	OFFHAND_CLASS_COUNT = 0x6,
};

enum PlayerHandIndex
{
	WEAPON_HAND_RIGHT = 0x0,
	WEAPON_HAND_LEFT = 0x1,
	NUM_WEAPON_HANDS = 0x2,
	WEAPON_HAND_DEFAULT = 0x0,
};

/* 1542 */
struct GlobalAmmo
{
	unsigned __int64 ammoType;
	int ammoCount;
};

struct ClipAmmo
{
	unsigned __int64 clipIndex;
	int ammoCount[2];
};

struct PlayerWeaponAnimArrays
{
	int nigger1;
	int nigger2;
	//XAnimParts *normalAnimArray[124];
	//XAnimParts *altAnimArray[124];
};


struct PlayerWeaponCommonState
{
	Weapon offHand;
	OffhandClass offhandPrimary;
	OffhandClass offhandSecondary;
	Weapon weapon;
	int weapFlags;
	float fWeaponPosFrac;
	float aimSpreadScale;
	int adsDelayTime;
	int spreadOverride;
	int spreadOverrideState;
	float fAimSpreadMovementScale;
	PlayerHandIndex lastWeaponHand;
	GlobalAmmo ammoNotInClip[15];
	ClipAmmo ammoInClip[15];
	int weapLockFlags;
	int weapLockedEntnum;
	float weapLockedPos[3];
	int weaponIdleTime;
	Weapon lastStowedWeapon;
	PlayerWeaponAnimArrays weaponAnimArrays;
};



struct playerState_s
{
	int commandTime;
	int pm_type;
	int pm_time;
	int pm_flags;
	int otherFlags;
	int linkFlags;
	int bobCycle;
	float origin[3];
	float velocity[3];
	int grenadeTimeLeft;
	int throwbackGrenadeOwner;
	int throwbackGrenadeTimeLeft;
	Weapon throwbackWeapon;
	int movingPlatformEntity;
	int remoteEyesEnt;
	int remoteEyesTagname;
	int remoteControlEnt;
	int remoteTurretEnt;
	int foliageSoundTime;
	int gravity;
	int speed;
	float delta_angles[3];
	int groundEntityNum;
	float vLadderVec[3];
	int jumpTime;
	float jumpOriginZ;
	int legsTimer;
	int legsAnim;
	int torsoTimer;
	int torsoAnim;
	int animMoveType;
	int damageTimer;
	int damageDuration;
	int flinch;
	int movementDir;
	int turnStartTime;
	int turnDirection;
	int turnRemaining;
	int corpseIndex;
	PlayerVehicleState vehicleState;
	int eFlags;
	playerEvents_t pe;
	int unpredictableEventSequence;
	int unpredictableEventSequenceOld;
	EntityEvent unpredictableEvents[4];
	int clientNum;
	int viewmodelIndex;
	float viewangles[3];
	int viewHeightTarget;
	float viewHeightCurrent;
	int viewHeightLerpTime;
	int viewHeightLerpTarget;
	int viewHeightLerpDown;
	float viewAngleClampBase[2];
	float viewAngleClampRange[2];
	int damageEvent;
	int damageYaw;
	int damagePitch;
	int damageCount;
	int damageFlags;
	int stats[4];
	float proneDirection;
	float proneDirectionPitch;
	float proneTorsoPitch;
	ViewLockTypes viewlocked;
	int viewlocked_entNum;
	float linkAngles[3];
	float linkWeaponAngles[3];
	int linkWeaponEnt;
	int loopSound;
	int groundRefEnt;
	int cursorHint;
	unsigned int cursorHintString;
	int cursorHintEntIndex;
	int cursorHintDualWield;
	int iCompassPlayerInfo;
	int radarEnabled;
	int radarBlocked;
	int radarMode;
	int radarStrength;
	int radarShowEnemyDirection;
	int sightedEnemyPlayersMask;
	int locationSelectionInfo;
	SprintState_s sprintState;
	float holdBreathScale;
	int holdBreathTimer;
	float moveSpeedScaleMultiplier;
	float grenadeCookScale;
	MantleState mantleState;
	SlideState slideState;
	float leanf;
	PlayerActiveWeaponState weapState[2];
	Weapon weaponsEquipped[15];
	PlayerEquippedWeaponState weapEquippedData[15];
	PlayerWeaponCommonState weapCommon;
	int meleeChargeDist;
	int meleeChargeTime;
	int meleeChargeEnt;
	int meleeServerResult;
	unsigned int airburstMarkDistance;
	unsigned int perks[2];
	unsigned int perkSlots[9];
	//ActionSlotType actionSlotType[4];
	//ActionSlotParam actionSlotParam[4];
	int weaponHudIconOverrides[6];
	int shellshockIndex;
	int shellshockTime;
	int shellshockDuration;
	float viewKickScale;
	float dofNearStart;
	float dofNearEnd;
	float dofFarStart;
	float dofFarEnd;
	float dofNearBlur;
	float dofFarBlur;
	float dofViewmodelStart;
	float dofViewmodelEnd;
	//objective_t objective[32];
	int deltaTime;
	int killCamEntity;
	int killCamLookAtEntity;
	int killCamClientNum;
	//$38A4C5C72B7CD27A063BA728E95FF065 hud;
	//OmnvarData rxvOmnvars[48];
	unsigned int partBits[6];
	int recoilScale;
	int stunTime;
	int clothType;
	//ClientOutlineData outlineData;
	//HudData hudData;
};


struct gclient_s
{
	playerState_s ps;
	//clientSession_t sess;
	//int flags;
	/*int spectatorClient;
	int cycleSpectatorClient;
	int cycleSpectatorTime;
	int lastCmdTime;
	iw::padding<4> mpviewer_padding;
	int buttons;
	int oldbuttons;
	int latched_buttons;
	int buttonsSinceLastFrame;
	float oldOrigin[3];
	float fGunPitch;
	float fGunYaw;
	AntilagAimHistoryFrame antilagAimHistory[8];
	int damage_blood;
	int damage_stun;
	float damage_from[3];
	int damage_fromWorld;
	int accurateCount;
	int accuracy_shots;
	int accuracy_hits;
	int inactivityTime;
	int inactivityWarning;
	int lastVoiceTime;
	int switchTeamTime;
	float currentAimSpreadScale;
	float prevLinkedInvQuat[4];
	bool prevLinkAnglesSet;
	bool link_rotationMovesEyePos;
	bool link_doCollision;
	bool link_useTagAnglesForViewAngles;
	bool link_useBaseAnglesForViewClamp;
	float linkAnglesFrac;
	viewClampState link_viewClamp;
	gentity_s *persistantPowerup;
	int portalID;
	int dropWeaponTime;
	int sniperRifleFiredTime;
	float sniperRifleMuzzleYaw;
	int PCSpecialPickedUpCount;
	EntHandle useHoldEntity;
	int useHoldTime;
	int useButtonDone;
	int iLastCompassPlayerInfoEnt;
	int compassPingTime;
	int damageTime;
	float v_dmg_roll;
	float v_dmg_pitch;
	float baseAngles[3];
	float baseOrigin[3];
	float swayViewAngles[3];
	float swayOffset[3];
	float swayAngles[3];
	float recoilAngles[3];
	float recoilSpeed[3];
	float fLastIdleFactor;
	int lastServerTime;
	Weapon lastWeapon;
	unsigned __int32 lastWeaponAltStatus : 1;
	unsigned __int32 previouslyFiring : 1;
	unsigned __int32 previouslyFiringLeftHand : 1;
	unsigned __int32 previouslyUsingNightVision : 1;
	unsigned __int32 previouslySprinting : 1;
	unsigned __int32 previouslySprintSliding : 1;
	int visionDuration[7];
	char visionName[7][64];
	int contactEntity;
	int lastStand;
	int lastStandTime;
	int hudElemLastAssignedSoundID;
	float lockedTargetOffset[3];
	scr_string_t attachShieldTagName;
	hintType_t hintForcedType;
	unsigned int hintForcedString;
	float grenadeThrowSpeedScale;
	float grenadeThrowSpeedUpScale;*/
};





struct level_locals_t
{
	gclient_s clients;
	/*OmnvarClientData *clientOmnvars;
	OmnvarGameData *gameOmnvars;
	gentity_s *gentities;
	int num_entities;
	gentity_s *firstFreeEnt;
	gentity_s *lastFreeEnt;
	Turret *turrets;
	sentient_s *sentients;
	int iSearchFrame;
	gagent_s *agents;
	int initializing;
	int clientIsSpawning;
	objective_t objectives[32];
	int maxclients;
	int maxagents;
	int framenum;
	int time;
	int previousTime;
	int frametime;
	int startTime;
	int teamScores[4];
	teammode_t teammode;
	int pingUpdateTime;
	bool teamHasRadar[4];
	bool teamRadarBlocked[4];
	int teamRadarStrength[4];
	int markedForEyesOn;
	int manualNameChange;
	int numConnectedClients;
	int sortedClients[12];
	SpawnVar spawnVar;
	int savepersist;
	EntHandle droppedWeaponCue[32];
	float fFogOpaqueDist;
	float fFogOpaqueDistSqrd;
	int currentPlayerClone;
	int currentAgentClone;
	trigger_info_t pendingTriggerList[256];
	trigger_info_t currentTriggerList[256];
	int pendingTriggerListSize;
	int currentTriggerListSize;
	int finished;
	int bPlayerIgnoreRadiusDamage;
	int bPlayerIgnoreRadiusDamageLatched;
	int currentEntityThink;
	__int64 openScriptIOFileHandles[1];
	char *openScriptIOFileBuffers[1];
	com_parse_mark_t currentScriptIOLineMark[1];
	cached_tag_mat_t cachedTagMat;
	int scriptPrintChannel;
	float compassMapUpperLeft[2];
	float compassMapWorldSize[2];
	float compassNorth[2];
	float pathnodeWorldSize[3];
	Vehicle *vehicles;
	int hudElemLastAssignedSoundID;
	outline_data_t outlineData[32];*/
};


// qword_1443F4600level_locals_t




