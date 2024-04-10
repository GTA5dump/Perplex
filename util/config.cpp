#include "stdafx.h"
#include "menu/submenus/main/settings/settingsthemeMenu.h"
#include "menu/submenus/main/settings/settingslanguagesMenu.h"

Config pConfig;

const char* Config::GetDirLocation(int specialenum) {
	wchar_t Path[MAX_PATH];
	char PathC[MAX_PATH];
	HRESULT result = SHGetFolderPath(nullptr, specialenum, nullptr, SHGFP_TYPE_CURRENT, Path);
	if (result != S_OK) {
		return "Error Locating Folder Path...";
	}
	wcstombs(PathC, Path, MAX_PATH);
	return PathC;
}

bool Config::InitializeLog() {
	sprintf_s(DocumentsFolder, GetDirLocation(CSIDL_PERSONAL));
	sprintf_s(PerplexGTARootFolder, "%s/Definitely not Perplex/Grand Theft Auto V"_Protect, DocumentsFolder);
	remove(pUtils.cprintf("%s/log.txt"_Protect, PerplexGTARootFolder));

	ifstream c_f(pUtils.cprintf("%s/log.txt"_Protect, PerplexGTARootFolder));
	if (DoesFileExist(pUtils.cprintf("%s/log.txt"_Protect, PerplexGTARootFolder))) {
		c_f.close();
		LOG_PUBLIC("Started new Perplex log."_Protect);
		return true;
	}

	return false;
}

bool Config::Initialize() {
	sprintf_s(LanguagesFolder, "%s/Translations", PerplexGTARootFolder);
	sprintf_s(ConfigsFolder, "%s/Configs", PerplexGTARootFolder);
	sprintf_s(ThemesFolder, "%s/Themes", PerplexGTARootFolder);
	sprintf_s(MenyooVehicleFolder, "%s/Menyoo Vehicles", PerplexGTARootFolder);
	sprintf_s(MapFolder, "%s/Maps", PerplexGTARootFolder);
	sprintf_s(OutfitsFolder, "%s/Outfits", PerplexGTARootFolder);
	//sprintf_s(SHVFolder, "%s/SHV", PerplexGTARootFolder);

	remove(pUtils.cprintf("%s/log.txt", PerplexGTARootFolder));

	if (!DoesFileExist(pUtils.cprintf("%s/ErrorHandler.exe"_Protect, PerplexGTARootFolder))) {
		LOG_PUBLIC("Error handler exe not found!"_Protect);
		pUtils.CloseProc();
		return false;
	}

	if (!DoesFileExist(pUtils.cprintf("%s/Options.json", ConfigsFolder))) {
		ofstream file(pUtils.cprintf("%s/Options.json", ConfigsFolder));
		file << "{}";
		file.close();
	}

	if (!DoesFileExist(pUtils.cprintf("%s/Misc.json", ConfigsFolder))) {
		ofstream file(pUtils.cprintf("%s/Misc.json", ConfigsFolder));
		file << "{}";
		file.close();
	} else {
		json object;
		ifstream file(pUtils.cprintf("%s/Misc.json", ConfigsFolder));
		file >> object;
		file.close();

		if (!object["Theme"]["Default"].is_null()) {
			SettingsThemeMenuVars::vars.CurrentLoadedTheme = object["Theme"]["Default"].get<string>();
			LOG_DEV("Loaded Custom Theme File");
		}

		if (!object["Language"]["Default"].is_null()) {
			SettingsLanguagesMenuVars::vars.CurrentLoadedLanguage = object["Language"]["Default"].get<string>();
			LOG_DEV("Loaded Language File");
		}
	}

	if (!DoesFileExist(pUtils.cprintf("%s/Overwatch.json", PerplexGTARootFolder))) {
		ofstream file(pUtils.cprintf("%s/Overwatch.json", PerplexGTARootFolder));
		file << "{}";
		file.close();
	}

	if (!DoesFileExist(pUtils.cprintf("%s/RockstarIDJoiner.json", PerplexGTARootFolder))) {
		ofstream file(pUtils.cprintf("%s/RockstarIDJoiner.json", PerplexGTARootFolder));
		file << "{}";
		file.close();
	}

	if (DoesFolderExist(DocumentsFolder) 
		&& DoesFolderExist(PerplexGTARootFolder) 
		&& DoesFolderExist(LanguagesFolder) 
		&& DoesFolderExist(ConfigsFolder) 
		&& DoesFolderExist(ThemesFolder) 
		&& DoesFolderExist(MenyooVehicleFolder)
		&& DoesFolderExist(MapFolder)) {
		LOG_DEV("Found Documents Folder: %s", DocumentsFolder);
		LOG_DEV("Found Perplex GTA Folder: %s", PerplexGTARootFolder);
		LOG_DEV("Found Translations Folder: %s", LanguagesFolder);
		LOG_DEV("Found Configs Folder: %s", ConfigsFolder);
		LOG_DEV("Found Themes Folder: %s", ThemesFolder);
		LOG_DEV("Found Menyoo Vehicle Folder: %s", MenyooVehicleFolder);
		LOG_DEV("Found Maps Folder: %s", MapFolder);
		return true;
	}

	LOG_DEV("Failed to initilize config data...");
	return false;
}

void Config::GetFilesFromDirectory(vector<string>& buffer, string folder, string extention) {
	buffer.clear();
	string loc = folder + "\\*" + extention;
	WIN32_FIND_DATAA fd;
	HANDLE hFind = FindFirstFileA(loc.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				string orig = fd.cFileName;
				string newstring = orig.substr(0, orig.size() - extention.size());
				buffer.push_back(newstring.c_str());
			}
		} while (FindNextFileA(hFind, &fd));
		FindClose(hFind);
	}
}

bool Config::DoesFileExist(string file) {
	ifstream i(file);
	return i.good();
}

bool Config::DoesFolderExist(const char* folder) {
	const std::string dirName_in = folder;
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;  
	return false;   
}

bool Config::ReadToggleFromConfig(bool& b00l, const char* submenu, const char* option) {
	LOG_DEV("%d, %s, %s", b00l, submenu, option);
	const char* file_loc = pUtils.cprintf("%s/Options.json", ConfigsFolder);

	if (!DoesFileExist(file_loc)) {
		LOG_DEV("Failed to find config file...");
		return false;
	}

	try {
		json object;
		ifstream file(file_loc);

		file >> object;

		file.close();

		if (!object[submenu][option].is_null()) {
			b00l = object[submenu][option].get<bool>();
		} else {
			WriteToggleToConfig(b00l, submenu, option);
		}

		return true;
	}
	catch (json::parse_error& e) {
		LOG_DEV("%s", e.what());
	} catch (...) {
		LOG_DEV("Unknown config error occoured!");
	}

	return true;
}

bool Config::WriteToggleToConfig(bool b00l, const char* submenu, const char* option) {
	LOG_DEV("%d, %s, %s", b00l, submenu, option);
	const char* file_loc = pUtils.cprintf("%s/Options.json", ConfigsFolder);

	if (!DoesFileExist(file_loc)) {
		LOG_DEV("Failed to find config file...");
		return false;
	}

	try {
		json object;

		ifstream file(file_loc);

		file >> object;

		file.close();

		ofstream out(file_loc);

		object[submenu][option] = b00l;

		out << setw(4) << object;
		out.close();
		return true;
	} catch(json::parse_error& e) {
		LOG_DEV("%s", e.what());
	} catch(...) {
		LOG_DEV("Unknown config error occoured!");
	}

	return true;
}

bool Config::WriteIntToConfig(int integer, const char* submenu, const char* option) {
	LOG_DEV("%d, %s, %s", integer, submenu, option);
	const char* file_loc = pUtils.cprintf("%s/Options.json", ConfigsFolder);

	if (!DoesFileExist(file_loc)) {
		LOG_DEV("Failed to find config file...");
		return false;
	}

	try {
		json object;

		ifstream file(file_loc);

		file >> object;

		file.close();

		ofstream out(file_loc);

		object[submenu][option] = integer;

		out << setw(4) << object;
		out.close();
	}
	catch (json::parse_error& e) {
		LOG_DEV("%s", e.what());
	}
	catch (...) {
		LOG_DEV("Unknown config error occoured!");
	}

	return true;
}

bool Config::ReadIntFromConfig(int& integer, const char* submenu, const char* option) {
	LOG_DEV("%d, %s, %s", integer, submenu, option);
	const char* file_loc = pUtils.cprintf("%s/Options.json", ConfigsFolder);

	if (!DoesFileExist(file_loc)) {
		LOG_DEV("Failed to find config file...");
		return false;
	}

	try {
		json object;
		ifstream file(file_loc);

		file >> object;

		file.close();

		if (!object[submenu][option].is_null()) {
			integer = object[submenu][option].get<int>();
		} else {
			WriteIntToConfig(integer, submenu, option);
		}

		return true;
	}
	catch (json::parse_error& e) {
		LOG_DEV("%s", e.what());
	}
	catch (...) {
		LOG_DEV("Unknown config error occoured!");
	}

	return true;
}

bool Config::WriteFloatToConfig(float fl0at, const char* submenu, const char* option) {
	LOG_DEV("%.3f, %s, %s", fl0at, submenu, option);
	const char* file_loc = pUtils.cprintf("%s/Options.json", ConfigsFolder);

	if (!DoesFileExist(file_loc)) {
		LOG_DEV("Failed to find config file...");
		return false;
	}

	try {
		json object;

		ifstream file(file_loc);

		file >> object;

		file.close();

		ofstream out(file_loc);

		object[submenu][option] = fl0at;

		out << setw(4) << object;
		out.close();
	}
	catch (json::parse_error& e) {
		LOG_DEV("%s", e.what());
	}
	catch (...) {
		LOG_DEV("Unknown config error occoured!");
	}

	return true;
}

bool Config::ReadFloatFromConfig(float& fl0at, const char* submenu, const char* option) {
	LOG_DEV("%.3f, %s, %s", fl0at, submenu, option);
	const char* file_loc = pUtils.cprintf("%s/Options.json", ConfigsFolder);

	if (!DoesFileExist(file_loc)) {
		LOG_DEV("Failed to find config file...");
		return false;
	}

	try {
		json object;
		ifstream file(file_loc);

		file >> object;

		file.close();

		if (!object[submenu][option].is_null()) {
			fl0at = object[submenu][option].get<float>();
		}
		else {
			WriteFloatToConfig(fl0at, submenu, option);
		}

		return true;
	}
	catch (json::parse_error& e) {
		LOG_DEV("%s", e.what());
	}
	catch (...) {
		LOG_DEV("Unknown config error occoured!");
	}

	return true;
}

