#pragma once
#include "menu/submenu.h"

class AllNetworkPlayersAbusiveAttachmentsMenu : public Submenu {
public:
	static AllNetworkPlayersAbusiveAttachmentsMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	AllNetworkPlayersAbusiveAttachmentsMenu() : Submenu() {}
	~AllNetworkPlayersAbusiveAttachmentsMenu();
};

namespace AllNetworkPlayersAbusiveAttachmentsMenuVars {
	struct Vars {

	};

	extern Vars vars;
}