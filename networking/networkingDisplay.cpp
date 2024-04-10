#include "stdafx.h"
#include "networkingDisplay.h"
#include "../networkingMenu.h"

using namespace NetworkingDisplayMenuVars;

namespace NetworkingDisplayMenuVars {
	Vars vars;
	
}

void NetworkingDisplayMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("Display", true, false);

	addOption(ToggleOption("Talking Players")
		.addToggle(vars.bDisplayTalkingPlayers)
		.addCanSaveToConfig("Display").addTranslation());

	addOption(ToggleOption("Player Count")
		.addToggle(vars.bDisplayPlayerCount)
		.addFunction([] {
			if (vars.bDisplayPlayerCount)
				vars.iDisplayPlayerCountID = pInfoRender.Register();
			else
				pInfoRender.Unregister(vars.iDisplayPlayerCountID);
		}).addCanSaveToConfig("Display")
		.addTranslation());

	addOption(ToggleOption("Display Leave Join Events")
		.addToggle(vars.bDisplayLeaveJoinEvents)
		.addCanSaveToConfig("Display"));
}

/*Update once when submenu is opened*/
void NetworkingDisplayMenu::UpdateOnce() {}

/*Update while submenu is active*/
void NetworkingDisplayMenu::Update() {}

/*Background update*/
void NetworkingDisplayMenu::FeatureUpdate() {
	if (vars.bDisplayTalkingPlayers) {
		pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
			if (NetworkIsPlayerTalking(player.Id) || NetworkPlayerHasHeadset(player.Id)) {
				pRenderer.DrawString(pUtils.cprintf("%s: %s", player.Name, NetworkIsPlayerTalking(player.Id) ? "~g~Talking" : "~p~Headset"), 0.010f, (0.315f + (0.025f * vars.iTalkingPlayersCount)), FontChaletLondon, 0.325f, { 255, 255, 255 });
				vars.iTalkingPlayersCount++;
			}
		});
		vars.iTalkingPlayersCount = 0;
	}

	if (vars.bDisplayPlayerCount) {
		pInfoRender.Update(vars.iDisplayPlayerCountID, pUtils.cprintf("Player Count: %d", NetworkGetNumConnectedPlayers()));
	}
}

/*Singleton*/
NetworkingDisplayMenu* _instance;
NetworkingDisplayMenu* NetworkingDisplayMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NetworkingDisplayMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
NetworkingDisplayMenu::~NetworkingDisplayMenu() { delete _instance; }