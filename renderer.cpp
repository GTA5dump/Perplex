#include "stdafx.h"

EngineRenderer pRenderer;

void EngineRenderer::NotifyMapColor(const char* pText, int color) { // 6 = red, 184 = green, 190 = yellow
	//LOG_DEV("MAP: %s", pText);
	_SetNotificationTextEntry("STRING");
	AddTextComponentSubstringPlayerName(pText);
	_SetNotificationBackgroundColor(color);
	_DrawNotification(false, true);
}

void EngineRenderer::DrawString(const char* text, float x, float y, int font, float scale, Color color, bool outline, int justify, float justifyfix) {
	SetTextFont(font);

	// justify: 0 - center, 1 - left, 2 - right (-1 = ignore)
	if (justify != -1) {
		SetTextWrap(0.0f, 0.958f - justifyfix);
		SetTextJustification(justify);
	}

	SetTextScale(0.0f, scale);
	SetTextColour(color.r, color.g, color.b, color.a);

	if (outline) SetTextOutline();
	SetTextCentre(justify == -2);
	BeginTextCommandDisplayText("STRING");
	AddTextComponentSubstringPlayerName(text);
	EndTextCommandDisplayText(x, y, 0);
}

void EngineRenderer::DrawSprite(Texture texture, float x, float y, float w, float h, float heading, Color color, bool renderIfNotStreamed) {
	bool streamed = HasStreamedTextureDictLoaded(texture.dict.c_str());
	if (streamed || renderIfNotStreamed) GRAPHICS::DrawSprite(texture.dict.c_str(), texture.id.c_str(), x, y, w, h, heading, color.r, color.g, color.b, color.a, 0);
	if (!streamed) RequestStreamedTextureDict(texture.dict.c_str(), false);
}

void EngineRenderer::DrawRect(float x, float y, float width, float height, Color color) {
	GRAPHICS::DrawRect(x, y, width, height, color.r, color.g, color.b, color.a, 0);
}

void EngineRenderer::DrawLine(Vector3 Point1, Vector3 Point2, Color color) {
	GRAPHICS::DrawLine(Point1.x, Point1.y, Point1.z, Point2.x, Point2.y, Point2.z, color.r, color.g, color.b, color.a);
}

void EngineRenderer::DrawTitle(const char* title) {
	string str = title;
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	DrawString(str.c_str(), 0.742f + pMenu.uiPos.x, 0.14587f + pMenu.uiPos.y, 0, 0.37f, pMenu.SubMenuTitleColor);
}

void EngineRenderer::RenderOpenTip() {
	if (pMenu.bRenderOpenTip) {
		if (pMenu.iOpenKey == VK_F4)
			pRenderer.DrawString("<font face=\"$gtaCash\">Perplex</font>\n~c~F4", 0.5f, 0.075f, FontChaletComprimeCologne, 0.450f, { pMenu.HeaderColor.r, pMenu.HeaderColor.g, pMenu.HeaderColor.b, 130 }, true, -2);
		else
			pRenderer.DrawString("<font face=\"$gtaCash\">Perplex</font>\n~c~", 0.5f, 0.075f, FontChaletComprimeCologne, 0.450f, { pMenu.HeaderColor.r, pMenu.HeaderColor.g, pMenu.HeaderColor.b, 130 }, true, -2);
	}
}

void EngineRenderer::Render() {
	pSubmenuHandler.GetTotalOptions() > pMenu.iMaxOptions ? fRenderOptions = pMenu.iMaxOptions : fRenderOptions = pSubmenuHandler.GetTotalOptions();

	RenderHeader();
	RenderSubHeader();
	RenderBackground();
	RenderOptionHighlight();
	RenderFooter();
	RenderGlobe();

	switch (pMenu.iHeaderStyle) {
	case 0:
		pRenderer.DrawString("Perplex", pMenu.fScaledXCoord + pMenu.uiPos.x, 0.07533f + pMenu.uiPos.y, FontPricedown, 1.0f, pMenu.TitleColor, true, -2);
		break;
	case 1:
		pRenderer.DrawSprite(Texture(pBackend.YTDName, "shopui_title_tattoos"), pMenu.fScaledXCoord + pMenu.uiPos.x, 0.09680f + pMenu.uiPos.y, 0.225f, 0.09f, 0.0f, { 255, 255, 255, 255 });
		break;
	default:
		//0w0
		break;
	}
}

void EngineRenderer::RenderHeader() {
	DrawRect(pMenu.fScaledXCoord + pMenu.uiPos.x, 0.09733f + pMenu.uiPos.y, 0.22500f, 0.09000f, pMenu.HeaderColor); //banner
}

void EngineRenderer::RenderSubHeader() {
	DrawRect(pMenu.fScaledXCoord + pMenu.uiPos.x, 0.16027f + pMenu.uiPos.y, 0.22500f, 0.03753f, pMenu.SubHeaderColor); //sub banner
	DrawString(pUtils.cprintf("%i / %i", pMenu.iCurrentOption + 1, pSubmenuHandler.GetTotalOptions()), 0.958f + pMenu.uiPos.x, 0.14587f, 0, 0.37f, pMenu.SubMenuTitleColor, false, JustifyRight);
}

void EngineRenderer::RenderBackground() {
	DrawRect(pMenu.fScaledXCoord + pMenu.uiPos.x, (0.198f + ((0.019f - 0.00040f) * (fRenderOptions - 1))) + pMenu.uiPos.y, 0.225f, (0.040f + ((0.037f + 0.00010f) * (fRenderOptions - 1))), pMenu.BackgroundColor); //background
}

void EngineRenderer::RenderOptionHighlight() {
	pMenu.iCurrentRenderingScroll = pUtils.Clamp(pMenu.iCurrentOption - pMenu.iScrollOffset > pMenu.iMaxOptions ? pMenu.iMaxOptions : (pMenu.iCurrentOption - pMenu.iScrollOffset) + 1, 0, pMenu.iMaxOptions);
	float diffrence = sqrt(pow(pMenu.iCurrentRenderingScroll - pMenu.fAnimatedScrollPos, 2));
	if (pMenu.bUseAnimatedScrollbar) pUtils.TransaitionFloatToValue(pMenu.fAnimatedScrollPos, pMenu.iCurrentRenderingScroll, diffrence < 2.5f ? pMenu.fAnimatedScrollIncrement : ((pMenu.fAnimatedScrollIncrement * (2.0f + (diffrence / 3.2f)))));
	DrawRect(pMenu.fScaledXCoord + pMenu.uiPos.x, (0.161333f + ((pMenu.bUseAnimatedScrollbar ? pMenu.fAnimatedScrollPos : pMenu.iCurrentRenderingScroll) * fOptionHeight)) + pMenu.uiPos.y, 0.225f, 0.03753f, pMenu.ScrollBarColor);
	DrawSprite(Texture("timerbars", "all_white_bg"), pMenu.fScaledXCoord - 0.016f + pMenu.uiPos.x, (0.161333f + ((pMenu.bUseAnimatedScrollbar ? pMenu.fAnimatedScrollPos : pMenu.iCurrentRenderingScroll) * fOptionHeight)) + pMenu.uiPos.y, 0.259f, 0.0365f, 360.0f, pMenu.ScrollBarFadeColor);
}

void EngineRenderer::RenderFooter() {
	if (pSubmenuHandler.GetTotalOptions() > pMenu.iMaxOptions) {
		int index = pSubmenuHandler.GetTotalOptions() > pMenu.iMaxOptions ? pMenu.iMaxOptions : pSubmenuHandler.GetTotalOptions();
		Vector3 res = GetTextureResolution("commonmenu", "shop_arrows_upanddown");
		DrawRect(pMenu.fScaledXCoord + pMenu.uiPos.x, ((0.1978f + ((0.03753f - 0.00030f) * index))) + pMenu.uiPos.y, 0.225f, 0.03753f, pMenu.SubHeaderColor); //sub banner
		DrawSprite(Texture("commonmenu", "shop_arrows_upanddown"), pMenu.fScaledXCoord + pMenu.uiPos.x, (0.1978f + ((0.03753f - 0.00030f) * index)) + pMenu.uiPos.y, ((res.x - 37) / pMenu.iScreenResolutionX), ((res.y - 35) / pMenu.iScreenResolutionY) - 0.0040f, 0.0f, pMenu.MenuTextColor);
	}
}

float func_444(float fParam0, float fParam1, float fParam2) { //game ting
	if (fParam1 == fParam2) {
		return fParam1;
	}
	auto fVar0 = fParam2 - fParam1;
	fParam0 -= round(fParam0 - fParam1 / fVar0) * fVar0;
	if (fParam0 < fParam1) {
		fParam0 += fVar0;
	}
	return fParam0;
}

void EngineRenderer::RenderGlobe() {
	if (pMenu.bRenderGlobe) {
		if (!HasScaleformMovieLoaded(pMenu.globe_handle)) {
			pMenu.globe_handle = RequestScaleformMovie("MP_MENU_GLARE");
		} else {
			_PushScaleformMovieFunction(pMenu.globe_handle, "SET_DATA_SLOT");
			_PushScaleformMovieFunctionParameterFloat(func_444(GetGameplayCamRot(2).z, 0.0f, 360.0f));
			_PopScaleformMovieFunctionVoid();
		}
		DrawScaleformMovie(pMenu.globe_handle, (pMenu.fScaledXCoord + 0.333f) + pMenu.uiPos.x, (0.04633f + 0.399f + 0.051f) + pMenu.uiPos.y, 0.98f, 1.02f + -0.032f, 255, 255, 255, 255, 0);
	}
}

void EngineRenderer::RenderTooltip(int id) {
	if (pMenu.bUseTooltip) {
		bool with_footer = (pSubmenuHandler.GetTotalOptions() > pMenu.iMaxOptions);
		int count = (with_footer ? pMenu.iMaxOptions + 1 : pSubmenuHandler.GetTotalOptions());
		float ycoord = (((count + 3) * 0.03753) + 0.11f) + -0.051 + pMenu.uiPos.y;
		if (HasScaleformMovieLoaded(iToolTipScaleform)) {
			ycoord += with_footer ? 0.0f : 0.009f;
			DrawScaleformMovie(iToolTipScaleform, pMenu.fScaledXCoord + pMenu.uiPos.x, ycoord + 0.5f, 0.22500f, 1.0f, 255, 255, 255, 255, 0);
			DrawRect(pMenu.fScaledXCoord + pMenu.uiPos.x, ycoord, 0.22500f, 0.003f, { 255, 255, 255 });
			_PushScaleformMovieFunction(iToolTipScaleform, "SET_TEXT");
			BeginTextCommandScaleformString("STRING");
			//SetTextScale(.42f, .42f);
			//SetTextColour(pMenu.MenuTextColor.m_r, pMenu.MenuTextColor.m_g, pMenu.MenuTextColor.m_b, pMenu.MenuTextColor.m_a);
			AddTextComponentSubstringPlayerName(sToolTipText.c_str());
			EndTextCommandScaleformString();
			sToolTipText.clear();
		} else {
			iToolTipScaleform = RequestScaleformMovie("TEXTFIELD");
		}
	}
}

float EngineRenderer::GetStringWidth(const char* str, int font, float fontsize) {
	if (font == FontChaletLondon) fontsize *= 0.75f;
	_BeginTextCommandWidth("STRING");
	AddTextComponentSubstringPlayerName(str);
	SetTextFont(font);
	SetTextScale(fontsize, fontsize);
	return _EndTextCommandGetWidth(font);
}

float EngineRenderer::GetStringHeight(int font, float fontsize) {
	return _GetTextScaleHeight(fontsize, font);
}

void EngineRenderer::NotifyBottom(const char* pText, int duration) {
	_SetNotificationBackgroundColor(12);
	BeginTextCommandPrint("STRING");
	AddTextComponentSubstringPlayerName(pText);
	EndTextCommandPrint(duration, 1);
}

void EngineRenderer::NotifyMap(const char* pText) {
	_SetNotificationTextEntry("STRING");
	AddTextComponentSubstringPlayerName(pText);
	EndTextCommandPrint(4000, true);
}

void EngineRenderer::NotifyStack(const char* pText) {
	if (CustomNotifyData.size() > 4) {
		CustomNotifyData.erase(CustomNotifyData.begin());
	}
	CustomNotifyData.push_back({ pText, GetGameTimer() });
}

void EngineRenderer::RenderCustomNotify() {
	int index = 0;
	for (auto item : CustomNotifyData) {
		if (item.second > GetGameTimer() - 5000) {
			pRenderer.DrawString(item.first.c_str(), 0.160f, 0.805f + (0.033f * (4 - index)), FontChaletLondon, 0.361f, { 255, 255, 255 });
			index++;
		} else {
			CustomNotifyData.erase(CustomNotifyData.begin() + index);
			//LOG_DEV("Removed Expired Notification // size: %d", CustomNotifyData.size());
		}
	}
}

void EngineRenderer::DrawInWorldBox(Entity entity, Color color) {
	Vector3 Min;
	Vector3 Max;
	GetModelDimensions(GetEntityModel(entity), &Min, &Max);
	float BoxWidth = Max.x * 2;
	float BoxLength = Max.y * 2;
	float BoxHeight = Max.z * 2;

	Vector3 P1 = GetOffsetFromEntityInWorldCoords(entity, (BoxWidth / 2) * -1, (BoxLength / 2), BoxHeight / 2);
	Vector3 P4 = GetOffsetFromEntityInWorldCoords(entity, BoxWidth / 2, (BoxLength / 2), BoxHeight / 2);
	Vector3 P5 = GetOffsetFromEntityInWorldCoords(entity, (BoxWidth / 2) * -1, (BoxLength / 2), (BoxHeight / 2) * -1);
	Vector3 P7 = GetOffsetFromEntityInWorldCoords(entity, BoxWidth / 2, (BoxLength / 2), (BoxHeight / 2) * -1);
	Vector3 P2 = GetOffsetFromEntityInWorldCoords(entity, (BoxWidth / 2) * -1, (BoxLength / 2)* -1, BoxHeight / 2);
	Vector3 P3 = GetOffsetFromEntityInWorldCoords(entity, BoxWidth / 2, (BoxLength / 2)* -1, BoxHeight / 2);
	Vector3 P6 = GetOffsetFromEntityInWorldCoords(entity, (BoxWidth / 2) * -1, (BoxLength / 2)* -1, (BoxHeight / 2) * -1);
	Vector3 P8 = GetOffsetFromEntityInWorldCoords(entity, BoxWidth / 2, (BoxLength / 2)* -1, (BoxHeight / 2) * -1);

	DrawLine(P1, P4, color);
	DrawLine(P1, P2, color);
	DrawLine(P1, P5, color);
	DrawLine(P2, P3, color);
	DrawLine(P3, P8, color);
	DrawLine(P4, P7, color);
	DrawLine(P4, P3, color);
	DrawLine(P5, P7, color);
	DrawLine(P6, P2, color);
	DrawLine(P6, P8, color);
	DrawLine(P5, P6, color);
	DrawLine(P7, P8, color);
}

