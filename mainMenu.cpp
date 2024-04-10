#include "stdafx.h"
#include "menu/submenus/mainMenu.h"
#include "menu/submenus/main/playerMenu.h"
#include "menu/submenus/main/weaponMenu.h"
#include "main/worldMenu.h"
#include "main/miscMenu.h"
#include "main/devMenu.h"
#include "main/teleportationMenu.h"
#include "main/vehicleMenu.h"
#include "main/spawnMenu.h"
#include "main/networkingMenu.h"
#include "main/settingsMenu.h"


using namespace MainMenuVars;
namespace MainMenuVars {

}

void MainMenu::Init() {
	SetName("Main Menu", true, true);

	addOption(SubmenuOption("Player")
		.addSubmenu<PlayerMenu>()
		.addTranslation());

	addOption(SubmenuOption("Vehicle")
		.addSubmenu<VehicleMenu>()
		.addTranslation());

	addOption(SubmenuOption("Spawn")
		.addSubmenu<SpawnMenu>()
		.addTranslation());

	addOption(SubmenuOption("Teleportation")
		.addSubmenu<TeleportationMenu>()
		.addTranslation());

	addOption(SubmenuOption("Weapon")
		.addSubmenu<WeaponMenu>()
		.addTranslation());

	addOption(SubmenuOption("World")
		.addSubmenu<WorldMenu>()
		.addTranslation());

	addOption(SubmenuOption("Networking")
		.addSubmenu<NetworkingMenu>()
		.addTranslation());

	addOption(SubmenuOption("Miscellaneous")
		.addSubmenu<MiscMenu>()
		.addTranslation());

	addOption(SubmenuOption("Settings")
		.addSubmenu<SettingsMenu>()
		.addTranslation());

#ifdef DEBUG
	addOption(SubmenuOption("Developer Testing")
		.addSubmenu<DevMenu>()); 
#endif

}

void MainMenu::UpdateOnce() {}

void MainMenu::Update() {}

void MainMenu::FeatureUpdate() {}

/*Singleton*/
MainMenu* _instance;
MainMenu* MainMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new MainMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
MainMenu::~MainMenu() { delete _instance; }

/*
==Changelog ==
- Added flying vehicle speed selector
- Added wheels to LSC
- Added Neons to LSC
- Added bullet proof tyres to LSC
- Added display crosshair
- Added change all weapon skins (separate to current weapon skin changer)
- Added upgrade current weapon to the max
- Added upgrade all weapons to the max
- Fixed max vehicle upgrades not upgrading all the way
- Fixed casino wheel crash (for some users)
- Improved teleport location list
- Improved vehicle max upgrade
*/