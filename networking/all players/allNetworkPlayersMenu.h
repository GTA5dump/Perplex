#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersMenu : public Submenu {
public:
	static AllNetworkPlayersMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersMenu() : Submenu() {}
	~AllNetworkPlayersMenu();
};

namespace AllNetworkPlayersMenuVars
{
	struct Vars {

	};

	extern Vars vars;
}