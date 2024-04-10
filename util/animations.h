#pragma once

struct sGuiAnim {
	float* pVarable;
	float fTarget;
	float fIncrement;

	function<void()> on_complete;
};

class GuiAnimations {
private:
	vector<sGuiAnim>vData;
	int tick;

	void EraseAnimTask(sGuiAnim& anim);
	bool IsVarableInUse(float* varable);

public:
	void Run();
	GuiAnimations& Do(float* varable, float target, float speed = 0.01f);

	GuiAnimations& CallOnComplete(function<void()> func) {
		vData.back().on_complete = func;
		return *this;
	}
};

extern GuiAnimations pGuiAnimations;