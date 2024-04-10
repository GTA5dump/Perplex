#pragma once
#include "menu/submenu.h"

class NetworkingDisplayMenu : public Submenu {
public:
	static NetworkingDisplayMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NetworkingDisplayMenu() : Submenu() {}
	~NetworkingDisplayMenu();
};

namespace NetworkingDisplayMenuVars
{
	struct Vars {
		bool bDisplayTalkingPlayers;
		bool bDisplayPlayerCount;
		bool bDisplayLeaveJoinEvents = true;
		int iTalkingPlayersCount;
		int iDisplayPlayerCountID;
	};

	extern Vars vars;
}