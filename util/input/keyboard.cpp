#include "stdafx.h"

Keyboard pKeyboard;

void Keyboard::OnKeyboardMessage(DWORD key, WORD repeats, BYTE scan_code, BOOL is_extended, BOOL is_with_alt, BOOL was_down_before, BOOL is_up_now) {
	/*Numpad shift fix*/
	if (key == 38) key = 104;
	if (key == 39) key = 102;
	if (key == 37) key = 100;
	if (key == 40) key = 98;

	if (static_cast<int>(key) < 255) {
		KeyStates[key].dwTime = GetTickCount();
		KeyStates[key].bIsWithAlt = is_with_alt;
		KeyStates[key].bWasDownBefore = was_down_before;
		KeyStates[key].bIsUpNow = is_up_now;
		if (!KeyStates[key].bWasDownBefore) KeyStates[key].bJustDown = !is_up_now;
		if (is_up_now) nLastKey = key;
	}
}

bool Keyboard::KeyDown(DWORD key) {
	if (!_IsTextChatActive() && !IsSocialClubActive()) {
		return (static_cast<int>(key) < 255) ? (GetAsyncKeyState(key) & 0x8000) : false;
	}
	return false;
}

bool Keyboard::KeyJustDown(DWORD key) {
	if (KeyStates[key].dwTime < GetTickCount()) {
		KeyStates[key].dwTime = GetTickCount() + 40;
		bool state = (GetAsyncKeyState(key) & 0x8000);
		if (!KeyStates[key].bWasDownBefore) {
			KeyStates[key].bWasDownBefore = state;
			return state;
		} else {
			KeyStates[key].bWasDownBefore = state;
			return false;
		}
	}
	return false;
}

bool Keyboard::KeyJustUp(DWORD key, bool exclusive) {
	return false;
}

bool KeyDown(DWORD key) {
	return pKeyboard.KeyDown(key);
}

bool KeyJustDown(DWORD key) {
	return pKeyboard.KeyJustDown(key);
}
