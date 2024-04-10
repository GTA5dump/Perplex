#pragma once

class SubmenuHandler {
private:
	Submenu* pMainSubmenu;
	Submenu* pCurrentSubmenu;
	Submenu* pPreviousSubmenu;
	Submenu* pNextSubmenu = pMainSubmenu;

	int nNextCurrentOption;
	int nNextScrollOffset;

	vector<Submenu*> Submenus;
	vector<TranslationString> Strings;

public:
	void Init();
	void Update(bool withInput);
	void ASyncUpdate();

	void AddSubmenu(Submenu* submenu) { Submenus.push_back(submenu); }
	int GetTotalOptions() { return nTotalOptions; }
	void SetSubmenu(Submenu* submenu);
	void SetSubmenuMain();
	void SetSubPrevious(bool resetPosition = false);
	Submenu* GetCurrentSubmenu() { return pCurrentSubmenu; }
	Submenu* GetPreviousSubmenu() { return pPreviousSubmenu; };
	vector<Submenu*> GetSubmenus() { return Submenus; }
	vector<TranslationString> getStrings() { return Strings; }


	template<typename T>
	bool IsCurrentSubmenuOfType() {
		return dynamic_cast<const T*>(GetCurrentSubmenu()) != nullptr;
	}

	int nTotalOptions;
	int nCurrentOptionWithoutBreaks;
	int nTotalOptionsWithoutBreaks;
};

extern SubmenuHandler pSubmenuHandler;