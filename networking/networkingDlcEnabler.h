#pragma once
#include "menu/submenu.h"

class NetworkingDlcEnablerMenu : public Submenu {
public:
	static NetworkingDlcEnablerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NetworkingDlcEnablerMenu() : Submenu() {}
	~NetworkingDlcEnablerMenu();
};

namespace NetworkingDlcEnablerMenuVars
{
	struct Vars {
		bool bXMASDLC;
		bool bValentineDLC;
		bool bHaloweenDLC;
	};

	extern Vars vars;
}