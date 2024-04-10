#include "stdafx.h"
#include "allNetworkPlayersTeleportMenu.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/networkPlayerTeleport.h"

using namespace AllNetworkPlayersTeleportMenuVars;

namespace AllNetworkPlayersTeleportMenuVars {
	Vars vars;
	
}

void AllNetworkPlayersTeleportMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersMenu>();
	SetName("Teleportation", true, false);

	addOption(ButtonOption("Teleport Players In Vehicle To Me")
		.addTranslation()
		.addFunction([]{
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerTeleportMenuVars::TeleportVehicleToMe(player);
			});
		}
	));

	addOption(BreakOption("Apartment Locations")
		.addTranslation());

	for (auto& ap : NetworkPlayerTeleportMenuVars::apartments) {
		addOption(ButtonOption(NetworkPlayerTeleportMenuVars::GetLocationFromID(ap.Id))
			.addFunction([&] {
				pPlayerManager.OnlinePlayerCallback(false, false, [=](SPlayer player) {
					pNatives.TriggerScriptEvent({ SCRIPTEVENTS::ECLIPSETELEPORT, player.Id, 0, 0, ap.Id, ap.Id }, 6, player.Id);
				});
			}
		));
	}
}

/*Update once when submenu is opened*/
void AllNetworkPlayersTeleportMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersTeleportMenu::Update() {}

/*Background update*/
void AllNetworkPlayersTeleportMenu::FeatureUpdate() {}

/*Singleton*/
AllNetworkPlayersTeleportMenu* _instance;
AllNetworkPlayersTeleportMenu* AllNetworkPlayersTeleportMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersTeleportMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersTeleportMenu::~AllNetworkPlayersTeleportMenu() { delete _instance; }