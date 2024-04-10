#pragma once

class EngineRenderer {
public:
	void DrawString(const char* text, float x, float y, int font, float scale, Color color, bool outline = false, int justify = -1, float justifyfix = 0.0f);
	void DrawSprite(Texture texture, float x, float y, float w, float h, float heading, Color color, bool renderIfNotStreamed = true);
	void DrawRect(float x, float y, float width, float height, Color color);
	void DrawLine(Vector3 Point1, Vector3 Point2, Color color);
	void DrawTitle(const char* title);

	void Render();
	void RenderHeader();
	void RenderSubHeader();
	void RenderBackground();
	void RenderOptionHighlight();
	void RenderFooter();
	void RenderTooltip(int id);
	void RenderGlobe();
	void RenderOpenTip();

	float GetStringWidth(const char* str, int font, float fontsize);
	float GetStringHeight(int font, float fontsize);

	void NotifyBottom(const char* textl, int duration = 4000);
	void NotifyMap(const char* pText);
	void NotifyMapColor(const char* pText, int color);
	void NotifyStack(const char* pText);
	void RenderCustomNotify();

	void DrawInWorldBox(Entity entity, Color color);

	char szTooltip[256];

	float fWidth = 0.225f;
	float fBgOpacity = 45;
	float fLineWidth = 0.0009f;
	float fHeaderHeight = 0.083f;
	float fRenderOptions;
	float fOptionHeight = 0.037f;
	float fSubHeaderHeight = fOptionHeight;
	float fFooterHeight = fOptionHeight;
	float fTextSize = 0.35f;
	int iTextFont = FontChaletLondon;
	float fOptionY;

	Vector2 Position = { 0.15f, 0.12f };

	Color TitleColor = { 225, 225, 225, 255 };
	Color HeaderOutlineColor = { 255, 0, 0, 255 };
	Color SubHeaderColor = { 0, 0, 0, 200 };
	Color BackgroundPrimaryColor = { 0, 0, 0, 255 };
	Color ScrollBarColor = { 200, 0, 0, 200 };
	Color OptionColor = { 255, 255, 255, 255 };

	string sToolTipText;
	int iToolTipScaleform;

private:
	vector<pair<string, int>>CustomNotifyData;
};

extern EngineRenderer pRenderer;