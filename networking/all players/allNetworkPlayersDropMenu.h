#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersDropMenu : public Submenu {
public:
	static AllNetworkPlayersDropMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersDropMenu() : Submenu() {}
	~AllNetworkPlayersDropMenu();
};

namespace AllNetworkPlayersDropMenuVars
{
	struct Vars {
		bool bMoneyDrop;
		bool bDropRandomWeapon;
		bool bDropHealthKit;
		bool bDropParachute;

		int iDropDelay = 190;
	};

	extern Vars vars;
}