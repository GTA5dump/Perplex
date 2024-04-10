#include "stdafx.h"
#include "allNetworkPlayersDropMenu.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/networkPlayerDrops.h"
#include "menu/submenus/main/weaponMenu.h"

using namespace AllNetworkPlayersDropMenuVars;

namespace AllNetworkPlayersDropMenuVars {
	Vars vars;
	
}

void AllNetworkPlayersDropMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersMenu>();
	SetName("Drops", true, false);

	addOption(NumberOption<int>(SCROLL, "Drop Delay")
		.addNumber(vars.iDropDelay, "%dms", 1).addMin(10).addMax(5000).addTranslation());

	addOption(ToggleOption("2.5k Money Drop")
		.addToggle(vars.bMoneyDrop).addTranslation());

	addOption(ButtonOption("Drop Random Weapon")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerDropsMenuVars::DropWeapon(player, WeaponMenuVars::WeaponHashList[GetRandomIntInRange(0, (NUMOF(WeaponMenuVars::WeaponHashList)) - 1)]);
			});
		}
	));

	addOption(ToggleOption("Drop Random Weapon Loop")
		.addToggle(vars.bDropRandomWeapon).addTranslation());

	addOption(ButtonOption("Drop Health Kit")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerDropsMenuVars::DropHealth(player);
			});
		}
	));

	addOption(ToggleOption("Drop Health Kit Loop")
		.addToggle(vars.bDropHealthKit).addTranslation());

	addOption(ButtonOption("Drop Parachute")
		.addTranslation()
		.addFunction([] { NetworkPlayerDropsMenuVars::DropParachute(GetSelectedPlayer()); }));

	addOption(ButtonOption("Drop Parachute")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerDropsMenuVars::DropParachute(player);
			});
		}
	));

	addOption(ToggleOption("Drop Parachute Loop")
		.addToggle(vars.bDropParachute).addTranslation());
}

/*Update once when submenu is opened*/
void AllNetworkPlayersDropMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersDropMenu::Update() {}

/*Background update*/
void AllNetworkPlayersDropMenu::FeatureUpdate() {
	pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
		if (vars.bMoneyDrop) 
			NetworkPlayerDropsMenuVars::MoneyDrop(player, vars.iDropDelay);

		if (vars.bDropRandomWeapon) 
			NetworkPlayerDropsMenuVars::DropWeapon(player, WeaponMenuVars::WeaponHashList[GetRandomIntInRange(0, (NUMOF(WeaponMenuVars::WeaponHashList)) - 1)]);

		if (vars.bDropHealthKit) 
			NetworkPlayerDropsMenuVars::DropHealth(player);

		if (vars.bDropParachute) 
			NetworkPlayerDropsMenuVars::DropParachute(player);
	});
}

/*Singleton*/
AllNetworkPlayersDropMenu* _instance;
AllNetworkPlayersDropMenu* AllNetworkPlayersDropMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersDropMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersDropMenu::~AllNetworkPlayersDropMenu() { delete _instance; }