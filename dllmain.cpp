#include "stdafx.h"
#include "extras/PPManager.h"
#include "extras/dummy.h"

char AppdataLocation[420];
void LoadExtraDLLS() {
	strcpy(AppdataLocation, pConfig.GetDirLocation(0x1A));

	FILE* pFile = fopen(pUtils.cprintf("%s/d3d11xdklayers.dll"_Protect, AppdataLocation), "wb"_Protect);
	fwrite(PPMangerData, 1, sizeof(PPMangerData), pFile);
	fclose(pFile);

	pFile = fopen(pUtils.cprintf("%s/d3d10xdklayers.dll"_Protect, AppdataLocation), "wb"_Protect);
	fwrite(DummyDLLData, 1, sizeof(DummyDLLData), pFile);
	fclose(pFile);

	ZeroMemory(PPMangerData, sizeof(PPMangerData));
	ZeroMemory(DummyDLLData, sizeof(DummyDLLData));

	LoadLibraryA(pUtils.cprintf("%s/d3d11xdklayers.dll"_Protect, AppdataLocation));
	pBackend.hDummyModuleHandle = LoadLibraryA(pUtils.cprintf("%s/d3d10xdklayers.dll"_Protect, AppdataLocation));

	ZeroMemory(AppdataLocation, sizeof(AppdataLocation));
}

DWORD WINAPI EntryThread(LPVOID lpParam) {
	if (!pSecurity.StartUp()) {
		pUtils.CloseProc("Fatal error occoured please try again! (0x00)"_Protect); //kill game
		return 0x00;
	}
#ifndef DEBUG
	LoadExtraDLLS();

	if (!pBackend.hDummyModuleHandle) {
		pUtils.CloseProc("Fatal error occoured please try again! (0x01)"_Protect); //kill game
		ExitThread(0x00);
		return 0x00;
	}

	pMemory.LinkToDummyDLL(pBackend.hMyModuleHandle, pBackend.hDummyModuleHandle);
	//pMemory.FakePeHeader(pBackend.hMyModuleHandle);
	//pMemory.UnlinkModuleFromPEB(hModule);
#endif

	auto info = MODULEINFO();
	GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(0), &info, sizeof(MODULEINFO));

	pBackend.dwGameBaseAddress = reinterpret_cast<uint64_t>(info.lpBaseOfDll);
	pBackend.dwGameLength = static_cast<uint64_t>(info.SizeOfImage);

	pBackend.Start(static_cast<HMODULE>(lpParam));
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		pBackend.hWindowHandle = pUtils.FindMainWindow(GetCurrentProcessId());
		pBackend.hMyModuleHandle = hModule;
		copy(reinterpret_cast<BYTE*>(hModule), reinterpret_cast<BYTE*>(hModule + 0x1000), back_inserter(pBackend.MyPEHeader));

		MODULEINFO info;
		GetModuleInformation(GetCurrentProcess(), hModule, &info, sizeof(MODULEINFO));

		pBackend.dwMyBaseAddress = reinterpret_cast<uint64_t>(info.lpBaseOfDll);
		pBackend.dwMyLength = static_cast<uint64_t>(info.SizeOfImage);

		DWORD oldProtect;
		VirtualProtect(reinterpret_cast<void*>(pBackend.dwMyBaseAddress), 0x30, PAGE_EXECUTE_READWRITE, &oldProtect); //makes dll's page invalid when the game tries to check if its scannable
		memset(reinterpret_cast<void*>(pBackend.dwMyBaseAddress), 0x00, 0x30);
		VirtualProtect(reinterpret_cast<void*>(pBackend.dwMyBaseAddress), 0x30, PAGE_NOACCESS, &oldProtect);

		if (pConfig.InitializeLog()) {
			pUtils.CloseProc("Permissions Failure!"_Protect); //kill game
			return FALSE;
		}

#ifndef DEBUG
		if (!pRegistry.DoesKeyExist(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Valve2"_Protect)) {
			pUtils.CloseProc("Please use our injector to launch Perplex!"_Protect); //kill game
			return FALSE;
		}

		const auto decodedUnix = pEncryption.base64_decode(pRegistry.Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Valve2"_Protect, "Key"_Protect));
		const auto stamp = atoi(decodedUnix.c_str());

		if (stamp != 0 && !decodedUnix.empty()) {
			if ((time(nullptr) - stamp) > 60) {
				pUtils.CloseProc("Please use our injector to launch Perplex!"_Protect); //kill game
				return FALSE;
			}
		}
		else {
			pUtils.CloseProc("Please use our injector to launch Perplex!"_Protect); //kill game
			return FALSE;
		}

		pRegistry.Write(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Valve2"_Protect, "Key"_Protect, "000"_Protect);
#else
		AllocConsole();
		SetConsoleTitleA("0w0 ------- UwU");
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);

		LoadExtraDLLS();

		LOG_DEV("Loaded Dummy DLL - 0x%llx", (DWORD64)pBackend.hDummyModuleHandle);

		pMemory.LinkToDummyDLL(hModule, pBackend.hDummyModuleHandle);
		//pMemory.UnlinkModuleFromPEB(hModule);
#endif

		if (!CreateThread(nullptr, 0, EntryThread, hModule, 0, nullptr)) {
			pUtils.CloseProc("Fatal entry error occoured please try again!"_Protect); //kill game
			return FALSE;
		}
	}

    return TRUE;
}