#pragma once

class Keyboard {
public:
	void OnKeyboardMessage(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);
	bool KeyDown(DWORD key);
	bool KeyJustUp(DWORD key, bool exclusive = true);
	bool KeyJustDown(DWORD button);
	void ResetKeyState(DWORD key);
	int GetLastKey() { return nLastKey; }
private:
	int nLastKey;
	int nNowPeriod = 100;
	int nMaxDown = 600000; // ms

	struct {
		DWORD64 dwTime;
		BOOL bIsWithAlt;
		BOOL bWasDownBefore;
		BOOL bIsUpNow;
		bool bJustUp;
		bool bJustDown;
	} KeyStates[255];
};

extern Keyboard pKeyboard;

bool KeyDown(DWORD key);
bool KeyJustDown(DWORD key);