#pragma once

namespace ObjectSpawnMenuVars {
	struct sObjectData;
}

struct InfoBoxIDS {
	int ProfileItemIndex = 0;
	int LeftItemIndex = 0;
	int RightItemIndex = 0;

	void Reset() {
		ProfileItemIndex = 0;
		LeftItemIndex = 0;
		RightItemIndex = 0;
	}
};

class InfoBox {
private:
	enum InfoBoxTextTypes {
		Profile,
		Left,
		Right,
		Across
	};

	InfoBoxIDS PlayerInfoboxItemPos;
	InfoBoxIDS ObjectCreatorInfoboxItemPos;
	InfoBoxIDS ObjectManagerInfoboxItemPos;
	InfoBoxIDS* pNextRenderInfoboxIDS = nullptr;

	void AddInfoBoxItem(string name, string value, InfoBoxTextTypes type, bool requirement = true);
	void DrawPlayerPicture(SPlayer& player);
public:
	queue<SPlayer*> GeoLocationLookups;

	void RenderPlayerInfo(SPlayer& player);
	void RenderObjectCreatorInfo(Object object);
	void RednerObjectManagerInfo(ObjectSpawnMenuVars::sObjectData object);
	void GEOUpdate();

	bool bCanShowPlayerInfo;
	bool bShowInfoboxWhenClosed;

	float plusX;
};
extern InfoBox pInfoBox;