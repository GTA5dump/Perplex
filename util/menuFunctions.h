#pragma once
#include "menu/submenus/main/miscMenu.h"


static bool IsOpenPressed() {
	if (pMenu.IsMenuInputDisabled()) return false;
	// Open menu - RB + LB / open key + for some reason Q and E?
	return ((IsDisabledControlPressed(2, INPUT_FRONTEND_RB) && IsDisabledControlPressed(2, INPUT_FRONTEND_LEFT)) || KeyJustDown(pMenu.iOpenKey));
}

static bool IsAJPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	return IsDisabledControlJustReleased(2, INPUT_FRONTEND_ACCEPT) || KeyDown(VK_NUMPAD5);
}

static bool IsBJPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	return IsDisabledControlJustReleased(2, INPUT_FRONTEND_CANCEL) || KeyDown(VK_NUMPAD0);
}

static bool IsRPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	if (IsDisabledControlPressed(2, INPUT_FRONTEND_RIGHT) || KeyDown(VK_NUMPAD6)) return true; else return false;
}

static bool IsRJPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	if (IsDisabledControlJustReleased(2, INPUT_FRONTEND_RIGHT) || KeyDown(VK_NUMPAD6)) return true; else return false;
}

static bool IsLPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	if (IsDisabledControlPressed(2, INPUT_FRONTEND_LEFT) || KeyDown(VK_NUMPAD4)) return true; else return false;
}

static bool IsUpPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	if (IsDisabledControlPressed(2, INPUT_FRONTEND_UP) || KeyDown(VK_NUMPAD8)) return true; else return false;
}

static bool IsDPressed(bool overrideInput = false) {
	if (!overrideInput && pMenu.IsMenuInputDisabled()) return false;
	if (IsDisabledControlPressed(2, INPUT_FRONTEND_DOWN) || KeyDown(VK_NUMPAD2)) return true; else return false;
}

static bool IsOptionPressed() {
	static int iDelay;
	if (pMenu.IsMenuInputDisabled()) return false;
	if (iDelay <= GetTickCount()) {
		if (IsAJPressed()) {
			AUDIO::PlaySoundFrontend(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
			iDelay = GetTickCount() + 145;
			return true;
		}
	}
	return false;
}

static void Up() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iPreviousOption = pMenu.iCurrentOption;
	pMenu.iCurrentOption--;
	if (pMenu.iScrollOffset > 0 && pMenu.iCurrentOption - pMenu.iScrollOffset == -1)pMenu.iScrollOffset--;
	AUDIO::PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
	pMenu.iBreakScroll = 1;
}
static void Down() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iPreviousOption = pMenu.iCurrentOption;
	pMenu.iCurrentOption++;
	if (pMenu.iScrollOffset < pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions && pMenu.iCurrentOption - pMenu.iScrollOffset == pMenu.iMaxOptions) pMenu.iScrollOffset++;
	if (pSubmenuHandler.GetTotalOptions() >= pMenu.iMaxOptions && pMenu.iScrollOffset > pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions) pMenu.iScrollOffset = pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions;
	PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
	pMenu.iBreakScroll = 2;
}
static void Bottom() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption = pSubmenuHandler.GetTotalOptions() - 1;
	if (pSubmenuHandler.GetTotalOptions() >= pMenu.iMaxOptions) pMenu.iScrollOffset = pSubmenuHandler.GetTotalOptions() - pMenu.iMaxOptions;
	PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
	pMenu.iBreakScroll = 3;
	//pMenu.fAnimatedScrollPos = pUtils.Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : (pMenu.iCurrentOption - pMenu.iScrollOffset) + 1, 0, pMenu.iMaxOptions);
}
static void Top() {
	if (pSubmenuHandler.GetTotalOptions() == 0) return;
	pMenu.iCurrentOption = 0;
	pMenu.iScrollOffset = 0;
	PlaySoundFrontend(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
	pMenu.iBreakScroll = 4;
	//pMenu.fAnimatedScrollPos = pUtils.Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : (pMenu.iCurrentOption - pMenu.iScrollOffset) + 1, 0, pMenu.iMaxOptions);
}

static void MenuControls() {
	if (pMenu.IsMenuInputDisabled()) return;
	static int counter;
	static int delaytick = 150;
	pMenu.bLeftPress = false;
	pMenu.bRightPress = false;

	if (counter <= GetTickCount()) {
		if (IsOpenPressed()) {
			pMenu.bOpen = !pMenu.bOpen;

			SetCinematicButtonActive(!pMenu.bOpen);

			if (HasScaleformMovieLoaded(pRenderer.iToolTipScaleform)) {
				SetScaleformMovieAsNoLongerNeeded(&pRenderer.iToolTipScaleform);
			}

			if (HasScaleformMovieLoaded(pMenu.globe_handle)) {
				SetScaleformMovieAsNoLongerNeeded(&pMenu.globe_handle);
			}

			counter = GetTickCount() + delaytick;
		}
		else if (pMenu.IsOpen()) {
			if (IsUpPressed()) {
				if (pMenu.iCurrentOption == 0)
					Bottom();
				else
					Up();
				if (delaytick > 80) delaytick -= 15;
			}
			else if (IsDPressed()) {
				if (pMenu.iCurrentOption == pSubmenuHandler.GetTotalOptions() - 1)
					Top();
				else
					Down();
			}
			else if (IsBJPressed()) {
				PlaySoundFrontend(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
				pSubmenuHandler.SetSubPrevious();
			}
			else if (IsLPressed()) {
				PlaySoundFrontend(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
				pMenu.bLeftPress = true;
			}
			else if (IsRPressed()) {
				PlaySoundFrontend(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
				pMenu.bRightPress = true;
			}
			else {
				delaytick = 150;
				return;
			}
			if (delaytick > 80) delaytick -= 15;
			counter = GetTickCount() + delaytick;
		}
	}
}

static bool IsHotkeySavePressed() {
	return KeyJustDown(VK_F12);
}

static bool IsSavePressed() {
	return KeyJustDown(VK_F11);
}

static void PrepareMenu() {
	//SetMobilePhonePosition(0, 0, 0);
	//HideHudComponentThisFrame(5);
	//DisplayAmmoThisFrame(0);
	//SetRadarZoom(0);
	//DisplayCash(1);
	//Remove notifications
	//CLEAR_PRINTS();
	//ClearBrief();
	//ClearAllHelpMessages();
}

static void DisableControls() {
	using namespace HUDComponents;

	DisableControlAction(2, 141, true);
	DisableControlAction(2, 142, true);
	DisableControlAction(2, 337, true);
	DisableControlAction(2, 27, true);
	DisableControlAction(2, 166, true);
	DisableControlAction(2, 167, true);
	DisableControlAction(2, 168, true);
	DisableControlAction(2, 169, true);
	DisableControlAction(2, 19, true);
	DisableControlAction(2, 140, true);
	DisableControlAction(2, 199, true);
	DisableControlAction(0, INPUT_ARREST, true);
	DisableControlAction(0, INPUT_CONTEXT, true);
	DisableControlAction(0, INPUT_MELEE_BLOCK, true);
	DisableControlAction(2, INPUT_FRONTEND_UP, true);
	DisableControlAction(0, INPUT_HUD_SPECIAL, true);
	DisableControlAction(0, INPUT_VEH_CIN_CAM, true);
	DisableControlAction(0, INPUT_VEH_CIN_CAM, true);
	DisableControlAction(0, INPUT_VEH_HEADLIGHT, true);
	DisableControlAction(2, INPUT_FRONTEND_LEFT, true);
	DisableControlAction(2, INPUT_FRONTEND_DOWN, true);
	DisableControlAction(2, INPUT_FRONTEND_RDOWN, true);
	DisableControlAction(2, INPUT_FRONTEND_RIGHT, true);
	DisableControlAction(0, INPUT_CHARACTER_WHEEL, true);
	DisableControlAction(0, INPUT_VEH_RADIO_WHEEL, true);
	DisableControlAction(2, INPUT_FRONTEND_CANCEL, true);
	DisableControlAction(0, INPUT_MELEE_ATTACK_LIGHT, true);
	DisableControlAction(0, INPUT_MELEE_ATTACK_HEAVY, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_TREVOR, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_MICHAEL, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_FRANKLIN, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, true);

	/*HideHelpTextThisFrame();
	CAM::SetCinematicButtonActive(1);

	HideHudComponentThisFrame(HUD_HELP_TEXT);
	HideHudComponentThisFrame(HUD_VEHICLE_NAME);
	HideHudComponentThisFrame(HUD_AREA_NAME);
	HideHudComponentThisFrame(HUD_STREET_NAME);
	HideHudComponentThisFrame(HUD_VEHICLE_CLASS);

	SetInputExclusive(2, INPUT_FRONTEND_ACCEPT);
	SetInputExclusive(2, INPUT_FRONTEND_CANCEL);
	SetInputExclusive(2, INPUT_FRONTEND_DOWN);
	SetInputExclusive(2, INPUT_FRONTEND_UP);
	SetInputExclusive(2, INPUT_FRONTEND_LEFT);
	SetInputExclusive(2, INPUT_FRONTEND_RIGHT);
	DisableControlAction(0, INPUT_FRONTEND_RIGHT, true);
	DisableControlAction(0, INPUT_FRONTEND_DOWN, true);
	DisableControlAction(0, INPUT_FRONTEND_LEFT, true);
	DisableControlAction(0, INPUT_FRONTEND_UP, true);
	DisableControlAction(0, INPUT_ARREST, true);
	DisableControlAction(0, INPUT_CONTEXT, true);
	DisableControlAction(0, INPUT_MELEE_BLOCK, true);
	DisableControlAction(2, INPUT_FRONTEND_UP, true);
	DisableControlAction(0, INPUT_HUD_SPECIAL, true);
	DisableControlAction(0, INPUT_VEH_CIN_CAM, true);
	DisableControlAction(0, INPUT_VEH_CIN_CAM, true);
	DisableControlAction(0, INPUT_VEH_HEADLIGHT, true);
	DisableControlAction(2, INPUT_FRONTEND_LEFT, true);
	DisableControlAction(2, INPUT_FRONTEND_DOWN, true);
	DisableControlAction(2, INPUT_FRONTEND_RDOWN, true);
	DisableControlAction(2, INPUT_FRONTEND_RIGHT, true);
	DisableControlAction(0, INPUT_CHARACTER_WHEEL, true);
	DisableControlAction(0, INPUT_VEH_RADIO_WHEEL, true);
	DisableControlAction(2, INPUT_FRONTEND_CANCEL, true);
	DisableControlAction(0, INPUT_MELEE_ATTACK_LIGHT, true);
	DisableControlAction(0, INPUT_MELEE_ATTACK_HEAVY, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_TREVOR, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_MICHAEL, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_FRANKLIN, true);
	DisableControlAction(0, INPUT_SELECT_CHARACTER_MULTIPLAYER, true); */
}