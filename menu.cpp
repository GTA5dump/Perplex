#include "stdafx.h"
#include "submenus/main/networking/playerList/playerListMenu.h"

Menu pMenu;

void Menu::Initialize() {
	pSubmenuHandler.Init();
}

void Menu::Update() {
	if (bDisableGTAInputThisFrame) {
		DisableAllControlActions(0);
		bDisableGTAInputThisFrame = false;
		bDisabledGTAInputLastFrame = true;
	} else if (bDisabledGTAInputLastFrame && (!_IsTextChatActive() && !IsSocialClubActive())) {
		EnableAllControlActions(2); bDisabledGTAInputLastFrame = false;
	}

	if (bDisableMenuInputThisFrame) {
		bMenuInputDisabled = true;
		bDisableMenuInputThisFrame = false;
	} else bMenuInputDisabled = false;

	GetScreenResolution(&pMenu.iScreenResolutionX, &pMenu.iScreenResolutionY);
	pMenu.fScaledXCoord = static_cast<float>(pMenu.iScreenResolutionX) / (118.257f * 12.740f);

	MenuControls();

	if (pMenu.IsOpen()) {
		PrepareMenu();
		DisableControls();

		//Render menu GUI
		pRenderer.Render();

		//Update the menu
		pSubmenuHandler.Update(false);

		//RenderPlayerInfo player infobox
		if (pInfoBox.bCanShowPlayerInfo)
			pInfoBox.RenderPlayerInfo(GetSelectedPlayer());


	} else {
		//Renders the player infobox if they want it to show when they have the menu closed
		if (pInfoBox.bCanShowPlayerInfo && !pMenu.IsOpen() && pSubmenuHandler.GetCurrentSubmenu() != PlayerListMenu::GetInstance() && pInfoBox.bShowInfoboxWhenClosed)
			pInfoBox.RenderPlayerInfo(GetSelectedPlayer());

		pRenderer.RenderOpenTip();
	}
}

void Menu::ASyncUpdate() {
	pPlayerManager.Update();
}

bool Menu::IsSelected(int sub) {
	return pMenu.iCurrentRenderingScroll == (sub + 1);
}
