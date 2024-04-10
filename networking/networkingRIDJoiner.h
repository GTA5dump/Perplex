#pragma once
#include "menu/submenu.h"

class NetworkingRIDJoinerMenu : public Submenu {
public:
	static NetworkingRIDJoinerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NetworkingRIDJoinerMenu() : Submenu() {}
	~NetworkingRIDJoinerMenu();
};

namespace NetworkingRIDJoinerMenuVars
{
	struct Vars {
		vector<pair<string, int>>data;
	};

	void SavePlayerToRIDJoinList(SPlayer& player);

	extern Vars vars;
}