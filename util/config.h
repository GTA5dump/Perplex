#pragma once

class Config {
private:
	char DocumentsFolder[100];
	char PerplexGTARootFolder[100];
	char LanguagesFolder[100];
	char ConfigsFolder[100];
	char ThemesFolder[100];
	char MenyooVehicleFolder[100];
	char MapFolder[100];
	char OutfitsFolder[100];
	char SHVFolder[100];

public:
	bool Initialize();
	bool InitializeLog();
	void GetFilesFromDirectory(vector<string>& buffer, string folder, string extention);
	const char* GetDirLocation(int specialenum);
	bool DoesFileExist(string file);
	bool DoesFolderExist(const char* folder);
	bool WriteToggleToConfig(bool b00l, const char* submenu, const char* option);
	bool ReadToggleFromConfig(bool& b00l, const char* submenu, const char* option);
	bool WriteIntToConfig(int integer, const char* submenu, const char* option);
	bool ReadIntFromConfig(int& integer, const char* submenu, const char* option);
	bool WriteFloatToConfig(float fl0at, const char* submenu, const char* option);
	bool ReadFloatFromConfig(float& fl0at, const char* submenu, const char* option);

	string GetLanguagesPath() { return LanguagesFolder; }
	string GetConfigsPath() { return ConfigsFolder; }
	string GetPerplexGTARootPath() { return PerplexGTARootFolder; }
	string GetThemesPath() { return ThemesFolder;  }
	string GetMenyooVehiclesPath() { return MenyooVehicleFolder; }
	string GetMapPath() { return MapFolder; };
	string GetSHVPath() { return SHVFolder; }
	string GetOutfitsPath() { return OutfitsFolder;  }
};

extern Config pConfig;