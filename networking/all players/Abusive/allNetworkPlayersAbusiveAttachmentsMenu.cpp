#include "stdafx.h"
#include "menu/submenus/main/networking/all players/Abusive/allNetworkPlayersAbusiveAttachmentsMenu.h"
#include "menu/submenus/main/networking/all players/allNetworkPlayersAbusiveMenu.h"
#include "menu/submenus/main/networking/playerList/playerMenu/abusive/attachment/NetworkPlayerAbusiveObjectAttachment.h"


using namespace AllNetworkPlayersAbusiveAttachmentsMenuVars;

namespace AllNetworkPlayersAbusiveAttachmentsMenuVars {
	Vars vars;
}

void AllNetworkPlayersAbusiveAttachmentsMenu::Init() {
	SetParentSubmenu<AllNetworkPlayersAbusiveMenu>();
	SetName("Object Attachment", true, false);

	addOption(ButtonOption("Remove Attached Objects")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::RemoveAttachedObjects(player);
			});
		}
	));

	addOption(BreakOption("Preset")
		.addTranslation());

	addOption(ButtonOption("Dick")
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachDick(player);
			});
		}
	));

	addOption(ButtonOption("Minigun Dick")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachMinigunDick(player);
			});
		}	
	));

	addOption(ButtonOption("Snowman")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachSnowman(player);
			});
		}
	));

	addOption(ButtonOption("Egg Head")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachEggHead(player);
			});
		}
	));

	addOption(ButtonOption("Cone Head")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachConeHead(player);
			});
		}
	));

	addOption(ButtonOption("Rock Head")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachRockHead(player);
			});
		}
	));

	addOption(ButtonOption("Big Blob")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachBigBlob(player);
			});
		}
	));

	addOption(ButtonOption("Your Moms Dildo") //should of been genas dildo xD
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachMomsDildo(player);
			});
		}
	));


	addOption(ButtonOption("UFO")
		.addTranslation()
		.addFunction([] {
			pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer player) {
				NetworkPlayerAbusiveObjectAttachmentMenuVars::AttachUFO(player);
			});
		}
	)); 
}

/*Update once when submenu is opened*/
void AllNetworkPlayersAbusiveAttachmentsMenu::UpdateOnce() {}

/*Update while submenu is active*/
void AllNetworkPlayersAbusiveAttachmentsMenu::Update() {}

/*Background update*/
void AllNetworkPlayersAbusiveAttachmentsMenu::FeatureUpdate() {}

/*Singleton*/
AllNetworkPlayersAbusiveAttachmentsMenu* _instance;
AllNetworkPlayersAbusiveAttachmentsMenu* AllNetworkPlayersAbusiveAttachmentsMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new AllNetworkPlayersAbusiveAttachmentsMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
AllNetworkPlayersAbusiveAttachmentsMenu::~AllNetworkPlayersAbusiveAttachmentsMenu() { delete _instance; }