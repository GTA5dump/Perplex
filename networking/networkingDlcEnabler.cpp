#include "stdafx.h"
#include "networkingDlcEnabler.h"
#include "menu/submenus/main/networkingMenu.h"


using namespace NetworkingDlcEnablerMenuVars;

namespace NetworkingDlcEnablerMenuVars {
	Vars vars;

}

void NetworkingDlcEnablerMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("DLC Enabler", true, false);

	addOption(ToggleOption("Christmas DLC")
		.addToggle(vars.bXMASDLC).addTranslation()
		.addFunction([] { Global(262145).At(4732).As<bool>() = vars.bXMASDLC; })
		.addTooltip("Enables the games old christmas DLC items"));

	addOption(ToggleOption("Valentine DLC Items")
		.addToggle(vars.bValentineDLC).addTranslation()
		.addFunction([] {
			Global(262145).At(10896).As<bool>() = vars.bValentineDLC;
			Global(262145).At(10897).As<bool>() = vars.bValentineDLC;
			Global(262145).At(10898).As<bool>() = vars.bValentineDLC;
			Global(262145).At(10899).As<bool>() = vars.bValentineDLC;
			Global(262145).At(10900).As<bool>() = vars.bValentineDLC;
			Global(262145).At(12249).As<bool>() = vars.bValentineDLC;
			Global(262145).At(12250).As<bool>() = vars.bValentineDLC;
		})
	.addTooltip("Enables the games old valentine DLC items"));

	addOption(ToggleOption("Halloween DLC Items")
		.addToggle(vars.bHaloweenDLC).addTranslation()
		.addFunction([] {
			Global(262145).At(11567).As<bool>() = vars.bHaloweenDLC;
			Global(262145).At(10925).As<bool>() = vars.bHaloweenDLC;
			Global(262145).At(10918).As<bool>() = vars.bHaloweenDLC;
		})
	.addTooltip("Enables the games old halloween DLC items"));
}

/*Update once when submenu is opened*/
void NetworkingDlcEnablerMenu::UpdateOnce() {
}

/*Update while submenu is active*/
void NetworkingDlcEnablerMenu::Update() {}

/*Background update*/
void NetworkingDlcEnablerMenu::FeatureUpdate() {

}

/*Singleton*/
NetworkingDlcEnablerMenu* _instance;
NetworkingDlcEnablerMenu* NetworkingDlcEnablerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NetworkingDlcEnablerMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
NetworkingDlcEnablerMenu::~NetworkingDlcEnablerMenu() { delete _instance; }