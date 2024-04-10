#include "stdafx.h"
#include "networkingRIDJoiner.h"
#include "menu/submenus/main/networkingMenu.h"

using namespace NetworkingRIDJoinerMenuVars;

namespace NetworkingRIDJoinerMenuVars {
	Vars vars;

	void SavePlayerToRIDJoinList(SPlayer& player) {
		json object;
		auto file_loc = pUtils.cprintf("%s/RockstarIDJoiner.json", pConfig.GetPerplexGTARootPath().c_str());
		if (!pConfig.DoesFileExist(file_loc)) {
			pRenderer.NotifyStack("Failed to find RockstarIDJoiner.json...");
			return;
		}

		try {
			ifstream file(file_loc);
			file >> object;

			if (object["Logged"][player.Name].is_null()) {
				object["Logged"][player.Name] = player.iRockstarID;
			} else {
				pRenderer.NotifyStack("Player already in log...");
				file.close();
				return;
			}

			ofstream out(file_loc);
			out << setw(4) << object;
			out.close();
			file.close();
			pRenderer.NotifyStack(pUtils.cprintf("Added %s to rockstar id joiner config!", player.Name));
			NetworkingRIDJoinerMenu::GetInstance()->UpdateOnce();
		} catch (json::parse_error& e) {
			LOG_DEV("%s", e.what());
		} catch (...) {
			LOG_DEV("Unhandled exception...");
		}
	}
	
}

void NetworkingRIDJoinerMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("Rockstar ID Joiner", true, false);

	addOption(ButtonOption("Join By Rockstar ID")
		.addKeyboard("Enter A Rockstar ID", "", 15, [](const char* id) {
			//pNatives.JoinRockstarID(atoi(id));
			//pRenderer.NotifyStack("Started Join Process...");
			pRenderer.NotifyStack("This option is disabled for testing...");
	}).addTranslation());

	addOption(BreakOption("Saved Players")
		.addTranslation());
}

/*Update once when submenu is opened*/
void NetworkingRIDJoinerMenu::UpdateOnce() {
	ClearOptionsOffset(2);
	try {
		json object;
		auto file_loc = pUtils.cprintf("%s/RockstarIDJoiner.json", pConfig.GetPerplexGTARootPath().c_str());
		if (!pConfig.DoesFileExist(file_loc)) {
			pRenderer.NotifyStack("Failed to find RockstarIDJoiner.json!");
			return;
		}

		ifstream file(file_loc);
		file >> object;

		if (!object["Logged"].is_null()) {
			json item = object["Logged"];
			for (auto obj = item.begin(); obj != item.end(); obj++) {
				vars.data.push_back({ obj.key(), obj.value() });
				addOption(ButtonOption(pUtils.cprintf("%s ~c~[%d]", vars.data.at(vars.data.size() - 1).first.c_str(), vars.data.at(vars.data.size() - 1).second))
					.addFunction([] {
						auto& pp = vars.data.at(pMenu.iCurrentOption - 2);
						//pRenderer.NotifyStack(pUtils.cprintf("Attempting to join %s...", pp.first.c_str()));
						//pNatives.JoinRockstarID(pp.second);
						pRenderer.NotifyStack("This option is disabled for testing...");
					}
				));
			}
		} else {
			addOption(ButtonOption("None Found...")
				.addFunction([] {}));
		}
		file.close();
	} catch (json::parse_error & e) {
		LOG_DEV("%s", e.what());
	} catch (...) {
		LOG_DEV("Unhandled exception...");
	}
}

/*Update while submenu is active*/
void NetworkingRIDJoinerMenu::Update() {}

/*Background update*/
void NetworkingRIDJoinerMenu::FeatureUpdate() {}

/*Singleton*/
NetworkingRIDJoinerMenu* _instance;
NetworkingRIDJoinerMenu* NetworkingRIDJoinerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NetworkingRIDJoinerMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
NetworkingRIDJoinerMenu::~NetworkingRIDJoinerMenu() { delete _instance; }