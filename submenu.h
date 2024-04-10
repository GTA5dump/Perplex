#pragma once

class Submenu {
protected:
	vector<TranslationString> Strings;
	vector<shared_ptr<Option>> Options;
	TranslationString Name;
	Submenu* pParentSubmenu;

public:
	bool bCanBeSearched;
	int nOldCurrentOption;
	int nOldScrollOffset;

	virtual ~Submenu();
	Submenu() : Name(TranslationString("")), pParentSubmenu(nullptr), bCanBeSearched(false), nOldCurrentOption(0), nOldScrollOffset(0) {}

	vector<shared_ptr<Option>> GetOptions() { return Options; }

	void MenuUpdate(bool withInput);

	virtual void Init();
	virtual void UpdateOnce();
	virtual void Update();
	virtual void FeatureUpdate();

	template<typename T, typename = enable_if<is_base_of<Option, T>::value>>
	shared_ptr<T> addOption(T& option) {
		shared_ptr<T> ptr = make_shared<T>(option);
		Options.push_back(ptr);
		return ptr;
	}

	template<typename T, typename = enable_if<is_base_of<Option, T>::value>>
	shared_ptr<T>& addOption(shared_ptr<T>& option) {
		Options.push_back(option);
		return option;
	}

	template<typename T, typename = enable_if<is_base_of<Submenu, T>::value>>
	void SetParentSubmenu() {
		pParentSubmenu = T::GetInstance();
	}

	/*void SetParentSubmenu(Submenu*& sub) {
		pParentSubmenu = sub;
	}*/

	Submenu* GetParentSubmenu() { return pParentSubmenu; }

	void SetName(const char* name, bool hasTranslation, bool canBeSearched) {
		Name.Set(name);
		Name.SetHasTranslation(hasTranslation);
		bCanBeSearched = canBeSearched;
	}

	TranslationString& GetName() { return Name; }
	vector<TranslationString> GetStrings() { return Strings; }

	void ClearOptions() {
		Options.clear();
	}

	void ClearOptionsOffset(int offset) {
		if (offset > Options.size()) return;
		Options.resize(offset);
	}
};