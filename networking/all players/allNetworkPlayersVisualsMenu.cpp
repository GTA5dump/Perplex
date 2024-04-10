#include "stdafx.h"
#include "allNetworkPlayersVisualsMenu.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/networkPlayerVisuals.h"

using namespace AllNetworkPlayersVisualsMenuVars;

namespace AllNetworkPlayersVisualsMenuVars {
	Vars vars;

	ScrollStruct<float>Distances[] = {
		{ "Unlimited", 9999999.9f },
		{ "50m", 50.0f },
		{ "100m", 100.0f },
		{ "500m", 500.0f },
		{ "1000m", 1000.0f },
		{ "2000m", 2000.0f },
		{ "3000m", 3000.0f },
		{ "4000m", 4000.0f },
		{ "5000m", 5000.0f }
	};
	
}

void AllNetworkPlayersVisualsMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersMenu>();
	SetName("Visuals", true, false);

	addOption(ScrollOption<float>(SCROLL, "Distance Limit")
		.addScroll(vars.iDistance, 0, NUMOF(Distances) - 1, Distances)
		.addCanSaveToConfig("Visuals", vars.iDistance).addTranslation());

	addOption(ToggleOption("Only Show Enemy Team")
		.addToggle(vars.bOnlyShowEnemyTeam)
		.addCanSaveToConfig("Visuals")
		.addTooltip("This will make the esp only show enemy players while in deathmatches").addTranslation());

	addOption(BreakOption("ESP Types")
		.addTranslation());

	addOption(ToggleOption("Nametag")
		.addToggle(vars.bNametagESP)
		.addCanSaveToConfig("Visuals").addTranslation());

	addOption(ToggleOption("Line")
		.addToggle(vars.bLineESP)
		.addCanSaveToConfig("Visuals").addTranslation());

	addOption(ToggleOption("3D Box") 
		.addToggle(vars.b3DBoxESP)
		.addCanSaveToConfig("Visuals").addTranslation());

	addOption(ToggleOption("Pointer")
		.addToggle(vars.bPointerESP)
		.addCanSaveToConfig("Visuals").addTranslation());

	addOption(ToggleOption("Foot Marker")
		.addToggle(vars.bFootMarkerESP)
		.addCanSaveToConfig("Visuals").addTranslation());
}

/*Update once when submenu is opened*/
void AllNetworkPlayersVisualsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersVisualsMenu::Update() {}

/*Background update*/
void AllNetworkPlayersVisualsMenu::FeatureUpdate() {
	pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
		if (player.Team != GetLocalPlayer().Team || !vars.bOnlyShowEnemyTeam || GetLocalPlayer().Team == -1) {
			if (pUtils.GetDistanceBetweenCoords(GetLocalPlayer().Coords, player.Coords) <= Distances[vars.iDistance].Result) {
				if (vars.bNametagESP && !player.bNametagESP)
					NetworkPlayerVisualsMenuVars::NametagESP(player);

				if (vars.bLineESP && !player.bLineESP)
					NetworkPlayerVisualsMenuVars::_LineESP(player);

				if (vars.b3DBoxESP && !player.b3DBoxESP)
					NetworkPlayerVisualsMenuVars::_3DBoxESP(player);

				if (vars.bPointerESP && !player.bPointerESP)
					NetworkPlayerVisualsMenuVars::PointerESP(player);

				if (vars.bFootMarkerESP && !player.bFootMarkerESP)
					NetworkPlayerVisualsMenuVars::FootMarkerESP(player);
			}
		}
	});
}

/*Singleton*/
AllNetworkPlayersVisualsMenu* _instance;
AllNetworkPlayersVisualsMenu* AllNetworkPlayersVisualsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersVisualsMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersVisualsMenu::~AllNetworkPlayersVisualsMenu() { delete _instance; }