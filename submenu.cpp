#include "stdafx.h"

void Submenu::MenuUpdate(bool withInput) {
	Update();
	pRenderer.DrawTitle(Name.Get());
	pSubmenuHandler.nCurrentOptionWithoutBreaks = 0;
	pSubmenuHandler.nTotalOptionsWithoutBreaks = 0;
	pSubmenuHandler.nTotalOptions = 0;
	vector<shared_ptr<Option>> tempOptions;
	tempOptions.reserve(Options.size());
	if (Options.size() > 0) {
		int relativeOptionPosition = 0, visibilityOffset = 0;
		for (int i = 0; i < Options.size(); i++) {
			if (Options.at(i)->IsVisible()) {
				tempOptions.push_back(Options.at(i));
				visibilityOffset++;
				pSubmenuHandler.nTotalOptions++;
				if (!Options.at(i)->IsBreak()) {
					if (visibilityOffset <= pMenu.iCurrentOption) pSubmenuHandler.nCurrentOptionWithoutBreaks++;
					pSubmenuHandler.nTotalOptionsWithoutBreaks++;
				}
			}
		}
		for (int i = pMenu.iScrollOffset; i < pMenu.iScrollOffset + pMenu.iMaxOptions; i++) {
			if (i >= 0 && i < tempOptions.size()) {
				if (relativeOptionPosition >= pMenu.iMaxOptions) break;
				tempOptions.at(i).get()->Render(relativeOptionPosition);
				if (pMenu.IsOpen() && withInput) tempOptions.at(i).get()->Input(relativeOptionPosition);
				if (relativeOptionPosition == pMenu.iCurrentOption - pMenu.iScrollOffset) {
					Option* option = tempOptions.at(i).get();
					pRenderer.sToolTipText = option->GetTooltip().Get();
					if (!pRenderer.sToolTipText.empty()) pRenderer.RenderTooltip(relativeOptionPosition);
					if (pMenu.IsOpen()) option->RenderSelected(relativeOptionPosition);
				} relativeOptionPosition++;
			}
		}
	}
}

Submenu::~Submenu() {}
void Submenu::Init() {}
void Submenu::UpdateOnce() {}
void Submenu::Update() {}
void Submenu::FeatureUpdate() {}
