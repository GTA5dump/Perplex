#pragma once
#include "menu/submenu.h"

class NetworkStatSpooferMenu : public Submenu {
public:
	static NetworkStatSpooferMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NetworkStatSpooferMenu() : Submenu() {}
	~NetworkStatSpooferMenu();
};

namespace NetworkStatSpooferMenuVars {
	struct Vars {
		bool bSpoofLevel;
		bool bSpoofWallet;
		bool bSpoofBank;
		bool bSpoofKills;
		bool bSpoofDeaths;

		int iSpoofLevel;
		int iSpoofWallet;
		int iSpoofBank;
		int iSpoofKills;
		int iSpoofDeaths;
	};

	extern Vars vars;
}