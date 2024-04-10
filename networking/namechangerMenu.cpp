#include "stdafx.h"
#include "namechangerMenu.h"
#include "menu/submenus/main/networkingMenu.h"

using namespace NameChangerMenuVars;

namespace NameChangerMenuVars {
	Vars vars;

	ScrollStruct<const char*> colors[] {
		TranslationString("Normal"), "",
		TranslationString("Red"), "~r~",
		TranslationString("Green"), "~g~",
		TranslationString("Blue"), "~b~",
		TranslationString("Yellow"), "~y~",
		TranslationString("Grey"), "~c~",
		TranslationString("Black"), "~v~",
		TranslationString("Purple"), "~p~"
	};

	ScrollStruct<const char*> effects[] {
		TranslationString("Normal"), "",
		TranslationString("Bold"), "~bold~",
		TranslationString("Italic"), "~italic~",
		TranslationString("New Line"), "~n~"
	};

	ScrollStruct<const char*> preset[] {
		TranslationString("Perplex Cheats"), "Perplex Cheats",
		TranslationString("perplexcheats.net"), "perplexcheats.net",
		TranslationString("Rockstar Admin"), "~÷~ Admin",
		TranslationString("Rockstar Support"), "~÷~ Support",
		TranslationString("Sub To Pewdiepie"), "~g~Sub To PewDiePie",
		TranslationString("I'm Not Cheating"), "~p~I'm Not Cheating",
		TranslationString("Dirty Cheater"), "~r~Dirty Cheater"
	};
}

void NameChangerMenu::Init() {
	SetParentSubmenu<NetworkingMenu>();
	SetName("Name Changer", true, false);

	addOption(ButtonOption("Custom Input")
		.addKeyboard("Enter Your Desired Name", "", 16, [](const char* name) {
			vars.sName = name;
		}).addTranslation());

	addOption(ScrollOption<const char*>(SCROLL, "Color")
		.addScroll(vars.iColorSelection, 0, NUMOF(colors) - 1, colors).addTranslation());

	addOption(ScrollOption<const char*>(SCROLL, "Effect")
		.addScroll(vars.iEffectSelection, 0, NUMOF(effects) - 1, effects).addTranslation());

	addOption(ButtonOption("Apply Custom Name")
		.addFunction([] {
			if (!vars.sName.empty()) {
				pNatives.ChangeName(pUtils.cprintf("%s%s%s", effects[vars.iEffectSelection].Result, colors[vars.iColorSelection].Result, vars.sName.c_str()));
				vars.sName.clear();
				pRenderer.NotifyBottom("Custom name applied!");
			}
			else {
				pRenderer.NotifyBottom("You have not inputted a custom name!");
			}
		}
	).addTranslation());

	addOption(ButtonOption("Revert Back To Original Name")
		.addTranslation()
		.addFunction([] { pNatives.RevertNameChange(); }));

	addOption(BreakOption("Preset")
		.addTranslation());

	for (auto item : preset) {
		addOption(ButtonOption(item.Name.Get())
			.addFunction([=] {
				pNatives.ChangeName(item.Result);
				vars.sName.clear();
				pRenderer.NotifyStack(pUtils.cprintf("Changed name to: %s", item.Result));
			}
		));
	}
}

/*Update once when submenu is opened*/
void NameChangerMenu::UpdateOnce() { }

/*Update while submenu is active*/
void NameChangerMenu::Update() {
	if (!vars.sName.empty())
		pRenderer.NotifyBottom(pUtils.cprintf("Preview: %s%s%s", effects[vars.iEffectSelection].Result, colors[vars.iColorSelection].Result, vars.sName.c_str()), 1);
}

/*Background update*/
void NameChangerMenu::FeatureUpdate() {}

/*Singleton*/
NameChangerMenu* _instance;
NameChangerMenu* NameChangerMenu::GetInstance() {
	if (_instance == nullptr) {
		_instance = new NameChangerMenu();
		_instance->Init();
		pSubmenuHandler.AddSubmenu(_instance);
	}
	return _instance;
}
NameChangerMenu::~NameChangerMenu() { delete _instance; }