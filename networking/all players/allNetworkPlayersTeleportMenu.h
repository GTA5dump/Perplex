#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersTeleportMenu : public Submenu {
public:
	static AllNetworkPlayersTeleportMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersTeleportMenu() : Submenu() {}
	~AllNetworkPlayersTeleportMenu();
};

namespace AllNetworkPlayersTeleportMenuVars
{
	struct Vars {

	};

	extern Vars vars;
}