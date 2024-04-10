#pragma once
#include "util/rainbowManager.h"

class Menu {
public:
	bool bDisableGTAInputThisFrame = false;
	bool bDisabledGTAInputLastFrame = false;
	bool bDisableMenuInputThisFrame = false;
	bool bMenuInputDisabled = false;

	void DisableAllInputThisFrame() { bDisableGTAInputThisFrame = true; bDisableMenuInputThisFrame = true; }
	void DisableGTAInputThisFrame() { bDisableGTAInputThisFrame = true; }
	void DisableMenuInputThisFrame() { bDisableMenuInputThisFrame = true; }
	void Update();
	void ASyncUpdate();
	void Initialize();

	bool IsMenuInputDisabled() { return bMenuInputDisabled; }
	bool IsOpen() { return bOpen; }
	bool IsSelected(int sub);

	bool bOpen;
	bool bFirstOpen;
	bool bLeftPress;
	bool bRightPress;
	bool bRenderOpenTip = true;
	bool bRenderGlobe = true;
	bool bToggleNotification;
	bool bPlayerlistInfoBox = true;
	bool bShowLocationsInInfobox = false;
	bool bDisplayPlayerInfoBox = true;
	bool bUseTooltip;
	bool bIsCustomYTDLoaded;
	bool bUseAnimatedScrollbar = true;

	int iMaxOptions = 14;
	int iCurrentOption = 0;
	int iPreviousOption = 0;
	int iCurrentRenderingScroll;
	int iScrollOffset;
	int iBreakScroll;
	int iScreenResolutionX;
	int iScreenResolutionY;
	int iOpenKey = VK_F4;
	int globe_handle;
	int iToggleStyle;
	int iSubmenuIdentifierStyle = 1;
	int iHeaderStyle = 1;

	float fScaledXCoord;
	float fScrollRenderPos;
	float fAnimatedScrollPos = 1.0f;
	float fAnimatedScrollIncrement = 0.2f;

	Vector2 Thingating = { 0.0f,  0.0f };

	Vector2 uiPos;
	Vector2 SpazTestCoords = { 0.01f, 0.665f }; //0.015f
	Vector2 SpazTestScale = { 0.325f, 0.025f };
	float fHeaderY = 0.0468f;


	vector<pair<Color*, bool*>> MenuColors;

	Color HeaderColor = { 0, 0, 0, 207 };
	Color SubHeaderColor = { 0, 0, 0, 210 };
	Color TitleColor = { 255, 255, 255 };
	Color SubMenuTitleColor = { 255, 255, 255 };
	Color BackgroundColor = { 0, 0, 0, 190 };
	Color MenuTextColor = { 255, 255, 255 };
	Color HighlightedOptionColor = { 0, 0, 0 };
	Color ScrollBarColor = { 255, 255, 255 };
	Color ScrollBarFadeColor = { 0, 0, 0, 120 };

	void ResetCurrentOption() { 
		iCurrentOption = 0;
		iScrollOffset = 0;
	}
};

extern Menu pMenu;