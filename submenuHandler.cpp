#include "stdafx.h"
#include "menu/submenus/mainMenu.h"

SubmenuHandler pSubmenuHandler;

void SubmenuHandler::Init() {
	pMainSubmenu = pCurrentSubmenu = MainMenu::GetInstance();
}

void SubmenuHandler::Update(bool withInput) {
	if (pCurrentSubmenu != nullptr) {
		pCurrentSubmenu->MenuUpdate(withInput);
		if (pNextSubmenu != nullptr) {
			pMenu.iCurrentOption = nNextCurrentOption;
			pMenu.iScrollOffset = nNextScrollOffset;
			pCurrentSubmenu = pNextSubmenu;
			pNextSubmenu = nullptr;
			pCurrentSubmenu->UpdateOnce();
		}
	}
}

void SubmenuHandler::ASyncUpdate() {
	for (auto& sub : Submenus) sub->FeatureUpdate();
}

void SubmenuHandler::SetSubmenu(Submenu* submenu) {
	pPreviousSubmenu = pCurrentSubmenu;
	pCurrentSubmenu->nOldCurrentOption = pMenu.iCurrentOption;
	pCurrentSubmenu->nOldScrollOffset = pMenu.iScrollOffset;
	nNextCurrentOption = 0;
	nNextScrollOffset = 0;
	pNextSubmenu = submenu;
}

void SubmenuHandler::SetSubPrevious(bool resetPosition) {
	pPreviousSubmenu = pCurrentSubmenu;
	if (pCurrentSubmenu->GetParentSubmenu() == nullptr) {
		SetSubmenuMain();
		pMenu.bOpen = false; 
	} else {
		pNextSubmenu = pCurrentSubmenu->GetParentSubmenu();
		nNextCurrentOption = resetPosition ? 0 : pNextSubmenu->nOldCurrentOption;
		nNextScrollOffset = resetPosition ? 0 : pNextSubmenu->nOldScrollOffset;
	}
}

void SubmenuHandler::SetSubmenuMain() {
	pNextSubmenu = pMainSubmenu;
	nNextCurrentOption = 0;
	nNextScrollOffset = 0;
}