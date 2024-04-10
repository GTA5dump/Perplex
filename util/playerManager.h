#pragma once

class SPlayer {
public:
	const char* Name;
	const char* NameFromHandle;
	Player Id;
	Ped Ped;
	Vehicle Vehicle_;
	Vehicle LastVehicle;
	Entity Entity;
	Weapon WeaponEntity;
	DWORD WeaponHash;

	int HeadshotHandle;

	int Health;
	int MaxHealth;
	int Team;

	bool bExists;
	bool bIsHost;
	bool bIsInInterior;
	bool bIsGodmode;
	bool bIsFriend;
	bool bIsInVehicle;
	bool bHasWeaponInHand;
	bool bVisible;
	bool bIsTalking;
	bool bIsShooting;
	bool bIsDead;
	bool bConnected;
	bool bIsCheater;;
	bool bKickInProgress;
	bool bGeoDataSet;
	bool bInOtherPlayersVehicle;

	string ip = "N/A";
	string port = "Wait...";
	string isp = "Wait...";
	string city = "Wait...";
	string country = "Wait...";
	string countryCode = "Wait...";
	string timezone = "Wait...";
	string regionName = "Wait...";

	char originalName[60];

	__int64 iRockstarID;

	Vector3 Coords;
	Vector2 W2S;
	Vector3 AttachedPlayerCoords;
	Vector3 AttachedPlayerRotation;
	float fHeading;
	
	// player vars here
	bool bPerplexUser;

	bool bCanUseMiniMenu;
	bool bMiniMenuSpawnVehicle;
	bool bMiniMenuFixVehicle;
	bool bMiniMenuVehicle180;
	bool bMiniMenuVehicleSlingshot;
	bool bMiniMenuRemoveVehicleGravity;
	bool bMiniMenuVehicleSuperGrip;
	bool bMiniMenuVehicleSlippyTyres;
	bool bMiniMenuLockVehicleDoors;
	bool bMiniMenuMaxUpgradeVehicle;
	bool bMiniMenuClone;
	bool bMiniMenuGiveAllWeapons;
	bool bMiniMenuMoneyDrop;

	bool bExplosionLoop;
	bool bForcefield;
	bool bIncapacitate;
	bool bCloneLoop;
	bool bAlwaysWanted;
	bool bShakeCamera;
	bool bTrollMoneyDrop;
	bool bGlitchPlayer;
	bool bKickFromVehicle;
	bool bAngryVehicles;
	bool bSoundSpam;
	bool bSpectateSpam;
	bool bBadSport;
	bool bRemoveBadSport;
	bool bGiveAllWeapons;
	bool bRape1;
	bool bRape2;
	bool bForceVisible;
	bool bMoneyGun;
	bool bOTR;
	bool bNeverWanted;
	bool bExplosionGun;
	bool bMoneyDrop;
	bool bMoneyDrop10k;
	bool bDropRandomWeapon;
	bool bDropHealthKit;
	bool bDropParachute;
	bool bFreezeVehicle;
	bool bPopTyres;
	bool bUnmovableVehicle;
	bool bLockVehicleDoors;
	bool bBoostVehicleOnHornPress;
	bool bSpinVehicle;
	bool bSlippyTyres;
	bool bSuperGrip;
	bool bRemoveGravityRules;
	bool bInvincibleVehicle;
	bool bAutoRepairVehicle;
	bool bInvisibleVehicle;
	bool bVehicleAttached;
	bool bNametagESP;
	bool bLineESP;
	bool b3DBoxESP;
	bool bPointerESP;
	bool bFootMarkerESP;

	int iRapeType;
	int iGiveStars;
	int iExplosionType;
	int iMoneyBeforeDrop;
	int iEarnedFromMoneyDrop;
	int iGiveAllWeaponsIndex;

	vector<Object>AttachedObjects;

	Vector3 GetBoneCoords(DWORD index) {
		return GetWorldPositionOfEntityBone(Ped, GetPedBoneIndex(Ped, index)); 
	}

	void Erase() {
		//memset((void*)this, 0x0, sizeof(SPlayer));
	}

	void Reset() {
		Id = -1;
		Ped = -1;
		Name = "NULL";
		//if (!IsPedheadshotValid(HeadshotHandle)) {
		//	UnregisterPedheadshot(HeadshotHandle);
		//	HeadshotHandle = NULL;
		//} 
	}
};

class PlayerManager {
public:
	SPlayer Players[34];
	SPlayer* pLocalPlayer;
public:
	PlayerManager() : pLocalPlayer(&Players[0]) {}
	
	void Update();
	SPlayer& GetPlayer(int index);
	SPlayer& GetLocalPlayer();

	void OnlinePlayerCallback(bool doMe, bool overrideExcludes, function<void(SPlayer&)> callback);
};

extern PlayerManager pPlayerManager;

SPlayer& GetPlayer(int index);
SPlayer& GetLocalPlayer();
SPlayer& GetSelectedPlayer();