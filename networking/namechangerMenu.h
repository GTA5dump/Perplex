#pragma once
#include "menu/submenu.h"

class NameChangerMenu : public Submenu {
public:
	static NameChangerMenu* GetInstance();
	void Init() override;
	void UpdateOnce() override;
	void Update() override;
	void FeatureUpdate() override;

	NameChangerMenu() : Submenu() {}
	~NameChangerMenu();
};

namespace NameChangerMenuVars
{
	struct Vars {
		string sName;

		int iColorSelection;
		int iEffectSelection;
	};

	extern Vars vars;
}