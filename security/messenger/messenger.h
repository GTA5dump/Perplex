#pragma once

#undef MessageBox
#undef SendMessage
#define MAX_MESSAGE_ENTRIES 64

enum MsgCommands {
	COMMAND_NULL,
	COMMAND_PING, // returns a pong, letting the cheat know the manager is still here (and vice versa)
	COMMAND_INITIALIZE_GAME_SAFE, // cheat sends a payload that will store the game
	COMMAND_HOOK_FUNCTION, // used for hooking functions
	COMMAND_CHALLENGE_MEMORY_INTEGRITY, // used for integrity checking the module, with custom sizes and a seed. Compared server side with a dumped.bin
	COMMAND_RESOLVE_SIGNATURES, // gets a big buffer of sig data, decrypts them, then sends them back
	COMMAND_GET_HWID_HASHES
};

struct Message {
	MsgCommands Command;
	void* pData;
	DWORD dwDataSize;

	Message() {
		dwDataSize = 0;
		pData = nullptr;
		Command = COMMAND_NULL;
	}
};

struct ManagerMessageBox {
	Message pOutbox[MAX_MESSAGE_ENTRIES];
	Message pInbox[MAX_MESSAGE_ENTRIES];
};

class Messenger {
public:
	bool bReceivedInitialPing;
	DWORD dwLastPing;
	bool bReceivedSignatures;
	bool bReceivedHWID;
	uint64_t dwManagerBaseAddress;
	uint64_t dwManagerSize;

	bool Initialize();
	bool IsValidEntry(Message message);
	void GetFirstMessage(Message* pMessage);
	void SendMessage(Message* message);
	bool HasInbox();

	static void HandleThread();
private:
	ManagerMessageBox* pBox;
};

extern Messenger pMessenger;
extern unordered_map<MsgCommands, void(*)(Message)> MessengerCommandTable;