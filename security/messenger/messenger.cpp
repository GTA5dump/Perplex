#include "stdafx.h"

Messenger pMessenger;
unordered_map<MsgCommands, void(*)(Message)> MessengerCommandTable;

void Messenger::HandleThread() {
	Message msg;
	if (pMessenger.HasInbox()) {
		pMessenger.GetFirstMessage(&msg);

		if (pMessenger.IsValidEntry(msg)) {
			MessengerCommandTable[msg.Command](msg);
		}
	}

	Sleep(250);
}
//RtlRegisterForWnfMetaNotification
//	uint64_t DbgPrintReturnControlC = (uint64_t)GetProcAddress(GetModuleHandleA("ntdll.dll"), "DbgPrintReturnControlC");
bool Messenger::Initialize() {
	//uint64_t RtlRegisterForWnfMetaNotification = (uint64_t)GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "RtlRegisterForWnfMetaNotification"_Protect);
	uint64_t DbgPrintReturnControlC = (uint64_t)GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "DbgPrintReturnControlC"_Protect);
	if (DbgPrintReturnControlC) {
		byte defaultBytes[] = { 0x4C, 0x8B, 0xDC, 0x49, 0x89, 0x4B, 0x08, 0x49 };
		//byte defaultBytes[] = { 0x48, 0x83, 0xEC, 0x58, 0x33, 0xC0, 0x48, 0x89 };
		if (!memcmp(reinterpret_cast<void*>(DbgPrintReturnControlC), defaultBytes, 8)) {
			LOG_PUBLIC("Manager not valid!"_Protect);
			pUtils.CloseProc();
			return false;
		}

		pBox = *(ManagerMessageBox**)DbgPrintReturnControlC;
		if (pBox) {
			pThreadPool.RegisterThread("H"_Protect, HandleThread);
			return true;
		}
	}

	return false;
}

bool Messenger::IsValidEntry(Message message) {
	return message.Command != COMMAND_NULL;
}

void Messenger::GetFirstMessage(Message* pMessage) {
	if (ValidPtr(pBox)) {
		for (int i = 0; i < MAX_MESSAGE_ENTRIES; i++) {
			if (pBox->pInbox[i].Command != COMMAND_NULL) {
				memcpy(pMessage, (void*)&pBox->pInbox[i], sizeof(Message));
				pBox->pInbox[i] = Message();
				return;
			}
		}
	}
}

bool Messenger::HasInbox() {
	if (ValidPtr(pBox)) {
		for (int i = 0; i < MAX_MESSAGE_ENTRIES; i++) {
			if (IsValidEntry(pBox->pInbox[i])) {
				return true;
			}
		}
	}

	return false;
}

void Messenger::SendMessage(Message* message) {
	if (ValidPtr(pBox)) {
		for (int i = 0; i < MAX_MESSAGE_ENTRIES; i++) {
			if (!IsValidEntry(pBox->pOutbox[i])) {
				pBox->pOutbox[i] = *message;
				return;
			}
		}
	}
}