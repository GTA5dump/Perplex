#include "stdafx.h"
#include "playerListMenu.h"
#include "../../networkingMenu.h"
#include "playerMenu/networkPlayerMenu.h"

using namespace PlayerListMenuVars;

namespace PlayerListMenuVars {
	Vars vars;
	
	const char* GenerateName(SPlayer& player) {
		static char name[60];
		ZeroMemory(name, 60);
		strcpy(name, pUtils.cprintf("%s ", player.Name));

		if (player.bPerplexUser) strcat(name, "~o~[Perplex]");
		if (player.bIsHost) strcat(name, "~y~[H]");
		if (player.bIsFriend) strcat(name, "~g~[F]");
		if (player.Id == GetLocalPlayer().Id) strcat(name, "~b~[ME]");
		//if (player.bIsGodmode && !player.bIsInInterior) strcat(name, "~r~[GOD]");
		if (player.bIsInVehicle) strcat(name, "~p~[V]");
		if (player.Id > 31) strcat(name, "~r~[SCTV]");

		return name;
	}
}

void PlayerListMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("Player List", true, false);

	addOption(ToggleOption("Display Infobox")
		.addToggle(pMenu.bPlayerlistInfoBox)
		.addCanSaveToConfig("Player List").addTranslation());

	addOption(ToggleOption("Display Infobox When Closed")
		.addToggle(pInfoBox.bShowInfoboxWhenClosed)
		.addCanSaveToConfig("Player List").addTranslation());

	addOption(BreakOption("Players")
		.addTranslation());
}

/*Update once when submenu is opened*/
void PlayerListMenu::UpdateOnce() {
	pInfoBox.bCanShowPlayerInfo = true;
}

/*Update while submenu is active*/
void PlayerListMenu::Update() {
	static int TIMER;

	pUtils.RunTimedFunction(&TIMER, 900, [&] {
		ClearOptionsOffset(3);

		if (GetLocalPlayer().bConnected && NetworkIsSessionActive()) {
			for (SPlayer& player : pPlayerManager.Players) {
				if (player.bConnected) {
					addOption(SubmenuOption(GenerateName(player))
						.addSubmenu<NetworkPlayerMenu>()
						.addCurrentOp([&] {
							if (DoesEntityExist(player.Ped)) {
								vars.iSelectedPlayer = player.Id;
								pRenderer.DrawInWorldBox(player.Entity, { 255, 255, 255, 255 });
								pRenderer.DrawLine(player.Coords, GetLocalPlayer().Coords, { 255, 255, 255, 255 });
							}
						}
					));
				}
			}
		} else {
			addOption(ButtonOption("Go Online To View Player List").addTranslation());
		}
	});
}

/*Background update*/
void PlayerListMenu::FeatureUpdate() {}

/*Singleton*/
PlayerListMenu* _instance;
PlayerListMenu* PlayerListMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new PlayerListMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
PlayerListMenu::~PlayerListMenu() { delete _instance; }