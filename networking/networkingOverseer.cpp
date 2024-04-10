#include "stdafx.h"
#include "networkingOverseer.h"
#include "../networkingMenu.h"
#include "playerList/playerMenu/networkPlayerAbusive.h"

using namespace NetworkingOverseerMenuVars;

namespace NetworkingOverseerMenuVars {
	Vars vars;
	
	ScrollStruct<int> Method[] = {
		"Kick", 0,
		"Crash", 1
	};

	bool is_number(const std::string& s) {
		std::string::const_iterator it = s.begin();
		while (it != s.end() && isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}

	bool AddToOverwatch(string pName) { //to be called from the player submenu and stuff
		json object;
		auto file_loc = pUtils.cprintf("%s/Overwatch.json", pConfig.GetPerplexGTARootPath().c_str());
		if (!pConfig.DoesFileExist(file_loc)) {
			pRenderer.NotifyMapColor("Failed to find overwatch.json...", 6);
			return false;
		}

		try {
			ifstream file(file_loc);
			file >> object;

			if (is_number(pName)) {
				if (object["Overwatch"]["rockstar_ids"][pName].is_null()) {
					object["Overwatch"]["rockstar_ids"][pName] = true;
				} else {
					file.close();
					return false;
				}
			} else {
				if (object["Overwatch"]["sc_names"][pName].is_null()) {
					object["Overwatch"]["sc_names"][pName] = true;
				} else {
					file.close();
					return false;
				}
			}

			ofstream out(file_loc);
			out << setw(4) << object;
			out.close();
			file.close();
			NetworkingOverseerMenu::GetInstance()->UpdateOnce();
		}
		catch(...) {
			pRenderer.NotifyMapColor("[Overwatch] Unknown erorr with overwatch.json format!", 6);
			return false;
		}
		return true;
	}

	void UpdateOverwatch(string pName, bool state) {
		json object;
		auto file_loc = pUtils.cprintf("%s/Overwatch.json", pConfig.GetPerplexGTARootPath().c_str());
		if (!pConfig.DoesFileExist(file_loc)) {
			pRenderer.NotifyMapColor("Failed to find overwatch.json...", 6);
			return;
		}

		ifstream file(file_loc);
		file >> object;
		ofstream out(file_loc);

		if (is_number(pName)) {
			if (!object["Overwatch"]["rockstar_ids"][pName].is_null()) {
				object["Overwatch"]["rockstar_ids"][pName] = state;
			} else {
				pRenderer.NotifyMapColor("Error finding this Rockstar ID in Overwatch.json!", 6);
			}
		} else {
			if (!object["Overwatch"]["sc_names"][pName].is_null()) {
				object["Overwatch"]["sc_names"][pName] = state;
			} else {
				pRenderer.NotifyMapColor("Error finding this name in Overwatch.json!", 6);
			}
		}

		out << setw(4) << object;
		out.close();
		file.close();
	}

	void ClearOverwatchFile() {
		auto file_loc = pUtils.cprintf("%s/Overwatch.json", pConfig.GetPerplexGTARootPath().c_str());
		if (!pConfig.DoesFileExist(file_loc)) {
			pRenderer.NotifyMapColor("Failed to find overwatch.json...", 6);
			return;
		}

		ofstream out(file_loc);
		out << "{}";
		out.close();
		NetworkingOverseerMenu::GetInstance()->UpdateOnce();
	}
}

void NetworkingOverseerMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("Overwatch", true, false);

	addOption(ToggleOption("Enable")
		.addToggle(vars.bEnable)
		.addCanSaveToConfig("Overwatch")
		.addTooltip("Enable the overwatch to kick blacklisted users"));

	addOption(ButtonOption("Add By Name")
		.addKeyboard("Type a name to add to the Overwatch list!", "", 20, [] (const char* thing){
			AddToOverwatch(thing);
	    })
		.addTooltip("Choose to add by name"));

	addOption(ButtonOption("Add By Rockstar ID")
		.addKeyboard("Type a rockstar ID to add to the Overwatch list!", "", 20, [] (const char* thing){
			AddToOverwatch(thing);
		})
		.addTooltip("Choose to add by rockstar ID"));

	addOption(ButtonOption("Clear Overwatch")
		.addFunction([] {
			ClearOverwatchFile();
		}
	)
	.addTooltip("Clears the overwatch.json file"));

	//stuff
	GetInstance()->UpdateOnce(); //to populate the overwatch vector
}

/*Update once when submenu is opened*/
void NetworkingOverseerMenu::UpdateOnce() {
	ClearOptionsOffset(4);
	vars.data.clear();

	try {
		json object;
		auto file_loc = pUtils.cprintf("%s/Overwatch.json", pConfig.GetPerplexGTARootPath().c_str());
		if (!pConfig.DoesFileExist(file_loc)) {
			LOG_DEV("Failed to find overwatch.json");
			return;
		}
		
		ifstream file(file_loc);
		file >> object;

		addOption(BreakOption("Blacklisted Rockstar ID's")
			.addTranslation());

		if (!object["Overwatch"]["rockstar_ids"].is_null()) {
			json item = object["Overwatch"]["rockstar_ids"];

			for (auto obj = item.begin(); obj != item.end(); obj++) {
				vars.data.push_back({ obj.key(), obj.value() });
				addOption(ToggleOption(vars.data.at(vars.data.size() - 1).first.c_str())
					.addToggle(vars.data.at(vars.data.size() - 1).second)
					.addFunction([] {
						auto& pp = vars.data.at(vars.data.size() - 1);
						UpdateOverwatch(pp.first.c_str(), pp.second);
					}
				));
			}
		} else {
			addOption(ButtonOption("None Found...")
				.addFunction([] {}));
		}

		addOption(BreakOption("Blacklisted Names")
			.addTranslation());

		if (!object["Overwatch"]["sc_names"].is_null()) {
			json item = object["Overwatch"]["sc_names"];

			for (auto obj = item.begin(); obj != item.end(); obj++) {
				vars.data.push_back({ obj.key(), obj.value() });
				addOption(ToggleOption(vars.data.at(vars.data.size() - 1).first.c_str())
					.addToggle(vars.data.at(vars.data.size() - 1).second)
					.addFunction([] {
						auto& pp = vars.data.at(vars.data.size() - 1);
						UpdateOverwatch(pp.first.c_str(), pp.second);
					}
				));
			}
		} else {
			addOption(ButtonOption("None Found...")
				.addFunction([] {}));
		}

		file.close();
	}
	catch (json::parse_error & e) {
		LOG_DEV("%s", e.what());
	}
	catch(...) {
		LOG_DEV("Unhandled exception...");
	}
}

/*Update while submenu is active*/
void NetworkingOverseerMenu::Update() {}

/*Background update*/
void NetworkingOverseerMenu::FeatureUpdate() {
	static int timer;
	if (vars.bEnable) {
		if (!vars.data.empty()) {
			pUtils.RunTimedFunction(&timer, 5000, [&] { //check every 5 secs
				pPlayerManager.OnlinePlayerCallback(false, false, [](SPlayer& player) {
					if (find(vars.data.begin(), vars.data.end(), pair<string, bool>(player.Name, true)) != vars.data.end()) {
						//players name is blacklisted
						if (DoesEntityExist(player.Ped)) {
							NetworkPlayerAbusiveMenuVars::NonHostKick(player);
							LOG_DEV("%s is blacklisted!", player.Name);
							
							if (!player.bKickInProgress)
								pRenderer.NotifyMapColor(pUtils.cprintf("[Overwatch] %s was blacklisted so he has been kicked!", player.Name), 6);
							
							player.bKickInProgress = true;
						}
					}

					if (find(vars.data.begin(), vars.data.end(), pair<string, bool>(pUtils.cprintf("%lld", player.iRockstarID), true)) != vars.data.end()) {
						//players rockstar id is blacklisted
						if (DoesEntityExist(player.Ped)) {
							NetworkPlayerAbusiveMenuVars::NonHostKick(player);
							LOG_DEV("%lld is blacklisted!", player.iRockstarID);

							if (!player.bKickInProgress)
								pRenderer.NotifyMapColor(pUtils.cprintf("[Overwatch] %s was blacklisted so he has been kicked!", player.Name), 6);
							
							player.bKickInProgress = true;
						}
					}
				});
			});
		}
	}
}

/*Singleton*/
NetworkingOverseerMenu* _instance;
NetworkingOverseerMenu* NetworkingOverseerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NetworkingOverseerMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
NetworkingOverseerMenu::~NetworkingOverseerMenu() { delete _instance; }