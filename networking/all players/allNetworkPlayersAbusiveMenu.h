#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersAbusiveMenu : public Submenu {
public:
	static AllNetworkPlayersAbusiveMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersAbusiveMenu() : Submenu() {}
	~AllNetworkPlayersAbusiveMenu();
};

namespace AllNetworkPlayersAbusiveMenuVars
{
	struct Vars {
		bool bExplode;
		bool bExplodeTalking;
		bool bForceField;
		bool bIncapacitate;
		bool bAlwaysWanted;
		bool bShakeCamera;
		bool bTrollMoneyBags;
		bool bGlitchPlayersLoop;
		bool bKickFromVehicleLoop;
		bool bAngryVehicles;
		bool bAnnoyingSoundSpam;
		bool bSpectateMessageSpam;
		bool bDiscoTime;
		bool bAlwaysNighttime;
		bool bAlwaysDaytime;
		bool bTheOldSwitcharoo;

		int iGiveStars;
		int iDiscoDelay = 300;
	};

	extern Vars vars;
}