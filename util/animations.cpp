#include "stdafx.h"
GuiAnimations pGuiAnimations;

void GuiAnimations::EraseAnimTask(sGuiAnim& anim) {
	vData.erase(remove_if(vData.begin(), vData.end(), [&](sGuiAnim& target) {
		return (target.pVarable == anim.pVarable);
	}), vData.end());
}

bool GuiAnimations::IsVarableInUse(float* varable) {
	for (auto data : vData) { //<- gay 
		if (data.pVarable == varable) {
			return true;
		}
	}
	return false;
}

void GuiAnimations::Run() { //call this from its own thread
	if (GetTickCount() > tick) {
		if (!vData.empty()) {
			for (auto data : vData){
				if (*data.pVarable != data.fTarget) {
					if (*data.pVarable > (data.fTarget + 0.005)) {
						*data.pVarable -= data.fIncrement;
						continue;
					} else if (*data.pVarable < (data.fTarget - 0.005)) {
						*data.pVarable += data.fIncrement;
						continue;
					}
				}
				*data.pVarable = data.fTarget;
				EraseAnimTask(data);
				data.on_complete();
			}
			tick = GetTickCount() + 10;
		}
	}
}

GuiAnimations& GuiAnimations::Do(float* varable, float target, float speed) {
	if (!IsVarableInUse(varable)) {
		vData.push_back({ varable, target, speed });
	} 
	return *this;
}
