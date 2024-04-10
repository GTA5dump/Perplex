#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersVisualsMenu : public Submenu {
public:
	static AllNetworkPlayersVisualsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersVisualsMenu() : Submenu() {}
	~AllNetworkPlayersVisualsMenu();
};

namespace AllNetworkPlayersVisualsMenuVars
{
	struct Vars {
		bool bNametagESP;
		bool bLineESP;
		bool b3DBoxESP;
		bool bPointerESP;
		bool bFootMarkerESP;
		bool bOnlyShowEnemyTeam;

		int iDistance;
	};

	extern Vars vars;
}