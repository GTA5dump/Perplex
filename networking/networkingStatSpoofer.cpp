#include "stdafx.h"
#include "networkingStatSpoofer.h"
#include "../networkingMenu.h"

using namespace NetworkStatSpooferMenuVars;

namespace NetworkStatSpooferMenuVars {
	Vars vars;

}

void NetworkStatSpooferMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("Stat Spoofing", true, false);

	addOption(NumberOption<int>(TOGGLE, "Level")
		.addToggle(vars.bSpoofLevel).addTranslation()
		.addNumber(vars.iSpoofLevel, "%d", 1).addMin(0).addMax(8000).setScrollSpeed(10));

	addOption(NumberOption<int>(TOGGLE, "Wallet")
		.addToggle(vars.bSpoofWallet).addTranslation()
		.addNumber(vars.iSpoofWallet, "%d", 1).addMin(0).addMax(INT_MAX).setScrollSpeed(10));

	addOption(NumberOption<int>(TOGGLE, "Bank")
		.addToggle(vars.bSpoofBank).addTranslation()
		.addNumber(vars.iSpoofBank, "%d", 1).addMin(0).addMax(INT_MAX).setScrollSpeed(10));

	addOption(NumberOption<int>(TOGGLE, "Kills")
		.addToggle(vars.bSpoofKills).addTranslation()
		.addNumber(vars.iSpoofKills, "%d", 1).addMin(0).addMax(INT_MAX).setScrollSpeed(10));

	addOption(NumberOption<int>(TOGGLE, "Deaths")
		.addToggle(vars.bSpoofDeaths).addTranslation()
		.addNumber(vars.iSpoofDeaths, "%d", 1).addMin(0).addMax(INT_MAX).setScrollSpeed(10));

}

/*Update once when submenu is opened*/
void NetworkStatSpooferMenu::UpdateOnce() {}

/*Update while submenu is active*/
void NetworkStatSpooferMenu::Update() {}

/*Background update*/
void NetworkStatSpooferMenu::FeatureUpdate() {
	if (NetworkIsSessionActive()) {
		if (vars.bSpoofLevel) {
			Global(Globals::PLAYER_BASE).At(GetLocalPlayer().Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_LEVEL).As<uint64_t>() = vars.iSpoofLevel;
		}

		if (vars.bSpoofWallet) {
			Global(Globals::PLAYER_BASE).At(GetLocalPlayer().Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_WALLET).As<uint64_t>() = vars.iSpoofWallet;
		}

		if (vars.bSpoofBank) {
			Global(Globals::PLAYER_BASE).At(GetLocalPlayer().Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_TOTAL).As<uint64_t>() = (vars.iSpoofBank - vars.iSpoofWallet);
		}

		if (vars.bSpoofKills) {
			Global(Globals::PLAYER_BASE).At(GetLocalPlayer().Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_KILLS).As<uint64_t>() = vars.iSpoofKills;
		}

		if (vars.bSpoofDeaths) {
			Global(Globals::PLAYER_BASE).At(GetLocalPlayer().Id, Globals::PLAYER_PADDING).At(Globals::PLAYER_OFFSET).At(Globals::PLAYER_OFFSET_DEATHS).As<uint64_t>() = vars.iSpoofDeaths;
		}
	}
}

/*Singleton*/
NetworkStatSpooferMenu* _instance;
NetworkStatSpooferMenu* NetworkStatSpooferMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NetworkStatSpooferMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
NetworkStatSpooferMenu::~NetworkStatSpooferMenu() { delete _instance; }