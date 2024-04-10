#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersPeacefulMenu : public Submenu {
public:
	static AllNetworkPlayersPeacefulMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersPeacefulMenu() : Submenu() {}
	~AllNetworkPlayersPeacefulMenu();
};

namespace AllNetworkPlayersPeacefulMenuVars
{
	struct Vars {
		bool bOffTheRadar;
		bool bNeverWanted;
		bool bMoneyGun;
		bool bExplosionGun;
	};

	extern Vars vars;
}