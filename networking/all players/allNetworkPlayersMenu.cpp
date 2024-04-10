#include "stdafx.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networkingMenu.h"
#include "allNetworkPlayersAbusiveMenu.h"
#include "allNetworkPlayersTeleportMenu.h"
#include "allNetworkPlayersVisualsMenu.h"
#include "allNetworkPlayersDropMenu.h"
#include "allNetworkPlayersVehicleMenu.h"
#include "allNetworkPlayersPeacefulMenu.h"

using namespace AllNetworkPlayersMenuVars;

namespace AllNetworkPlayersMenuVars {
	Vars vars;
	
}

void AllNetworkPlayersMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("All Players", true, false);

	addOption(SubmenuOption("Abusive")
		.addSubmenu<AllNetworkPlayersAbusiveMenu>()
		.addTranslation()
		.addTooltip("Fuck with them"));

	addOption(SubmenuOption("Peaceful")
		.addSubmenu<AllNetworkPlayersPeacefulMenu>()
		.addTranslation()
		.addTooltip("Be nice to them"));

	addOption(SubmenuOption("Teleportation")
		.addSubmenu<AllNetworkPlayersTeleportMenu>()
		.addTranslation()
		.addTooltip("Cutting edge teleportation technology"));

	addOption(SubmenuOption("Vehicle")
		.addSubmenu<AllNetworkPlayersVehicleMenu>()
		.addTranslation()
		.addTooltip("Mess with their vehicle"));

	addOption(SubmenuOption("Drops")
		.addSubmenu<AllNetworkPlayersDropMenu>()
		.addTranslation()
		.addTooltip("Drop items (e.g. money bags)"));

	addOption(SubmenuOption("Visuals")
		.addSubmenu<AllNetworkPlayersVisualsMenu>()
		.addTranslation()
		.addTooltip("Advanced ESP options"));
}

/*Update once when submenu is opened*/
void AllNetworkPlayersMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersMenu::Update() {}

/*Background update*/
void AllNetworkPlayersMenu::FeatureUpdate() {}

/*Singleton*/
AllNetworkPlayersMenu* _instance;
AllNetworkPlayersMenu* AllNetworkPlayersMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersMenu::~AllNetworkPlayersMenu() { delete _instance; }