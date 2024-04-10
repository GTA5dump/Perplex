#pragma once
#include "menu/submenu.h"

class NetworkingOverseerMenu : public Submenu {
public:
	static NetworkingOverseerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NetworkingOverseerMenu() : Submenu() {}
	~NetworkingOverseerMenu();
};

namespace NetworkingOverseerMenuVars
{
	struct Vars {
		bool bEnable = true;
		int iMethod;

		json JsonObject;

		vector<pair<string, bool>>data;
	};

	bool AddToOverwatch(string pName);

	extern Vars vars;
}