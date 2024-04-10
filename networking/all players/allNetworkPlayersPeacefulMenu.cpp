#include "stdafx.h"
#include "allNetworkPlayersPeacefulMenu.h"
#include "allNetworkPlayersMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/networkPlayerPeaceful.h"

using namespace AllNetworkPlayersPeacefulMenuVars;

namespace AllNetworkPlayersPeacefulMenuVars {
	Vars vars;
	
}

void AllNetworkPlayersPeacefulMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersMenu>();
	SetName("Peaceful", true, false);

	addOption(ButtonOption("Give All Weapons")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerPeacefulMenuVars::GiveAllWeapons(player);
			});
		}
	));

	addOption(ButtonOption("Christmas Snow")
		.addTranslation()
		.addFunction([] {
			//pBackend.iSetWeatherTimeout = GetGameTimer() + 10000;
			//pNatives.SetLobbyWeather("XMAS");
			pBackend.iSetSessionSnowTimeout = GetGameTimer() + 3500;
			pNatives.SyncLobbyWeather(1, 13, 76, 0);
		}
	));

	addOption(ButtonOption("Sunny Weather")
		.addTranslation()
		.addFunction([] {
			pNatives.SetLobbyWeather("SUNNY");
		}
	));

	addOption(ButtonOption("Set Time To Night")
		.addTranslation()
		.addFunction([] {
			NetworkOverrideClockTime(0, GetClockMinutes(), GetClockSeconds());
			pNatives.SyncLobbyTimeWithMyTime();
		}
	));

	addOption(ButtonOption("Set Time To Daytime")
		.addTranslation()
		.addFunction([] {
			NetworkOverrideClockTime(12, GetClockMinutes(), GetClockSeconds());
			pNatives.SyncLobbyTimeWithMyTime();
		}
	));

	addOption(ToggleOption("Give Unlimited Off The Radar")
		.addToggle(vars.bOffTheRadar).addTranslation());

	addOption(ToggleOption("Give Unlimited Never Wanted")
		.addToggle(vars.bNeverWanted).addTranslation());

	addOption(ButtonOption("Commend For Being Helpful")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerPeacefulMenuVars::CommendForBeingHelpful(player);
			});
		}
	));

	addOption(ButtonOption("Commend For Being Freindly")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerPeacefulMenuVars::CommendForBeingFreindly(player);
			});
		}
	));

	addOption(BreakOption("Weapon Mods")
		.addTranslation());

	addOption(ToggleOption("Give Money Gun")
		.addToggle(vars.bMoneyGun).addTranslation());

	addOption(ToggleOption("Give Explosion Gun")
		.addToggle(vars.bExplosionGun).addTranslation());

}

/*Update once when submenu is opened*/
void AllNetworkPlayersPeacefulMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersPeacefulMenu::Update() {}

/*Background update*/
void AllNetworkPlayersPeacefulMenu::FeatureUpdate() {
	pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
		if (vars.bOffTheRadar) 
			NetworkPlayerPeacefulMenuVars::OffTheRadar(player);

		if (vars.bNeverWanted) 
			NetworkPlayerPeacefulMenuVars::NeverWanted(player);

		if (vars.bMoneyGun) 
			NetworkPlayerPeacefulMenuVars::ModdedWeaponImpact(player, 0);

		if (vars.bExplosionGun) 
			NetworkPlayerPeacefulMenuVars::ModdedWeaponImpact(player, 1);

	});
}

/*Singleton*/
AllNetworkPlayersPeacefulMenu* _instance;
AllNetworkPlayersPeacefulMenu* AllNetworkPlayersPeacefulMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersPeacefulMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersPeacefulMenu::~AllNetworkPlayersPeacefulMenu() { delete _instance; }