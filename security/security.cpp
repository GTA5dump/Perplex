#include "stdafx.h"
#include <iphlpapi.h>
#pragma comment(lib, "iphlpapi")

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

Security pSecurity;

void Security::BSOD() {
	LOG_PUBLIC("Y0u're about to be blue screened, alas"_Protect);
	BOOLEAN bl;
	ULONG Response;
	RtlAdjustPrivilege(19, TRUE, FALSE, &bl);
	NtRaiseHardErrorSyscall(STATUS_ASSERTION_FAILURE, 0, 0, nullptr, 6, &Response);
	NtRaiseHardErrorSyscall(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, nullptr, 6, &Response);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, nullptr, 6, &Response);
	NtRaiseHardError(STATUS_FLOAT_MULTIPLE_FAULTS, 0, 0, nullptr, 6, &Response); 
}

void Security::BanUser() {
	pNetwork.Post("server_51"_Protect, "");
}

bool Security::StartUp() {
	const char* syscallAsm = "\x4C\x8B\xD1\xB8\x00\x00\x00\x00\x0F\x05\xC3";

	// NtQueryVirtualMemory
	int ntQueryVirtualMemory = 0;
	if (!pMemory.GetSyscall(GetModuleHandleA("ntdll.dll"_Protect), 512, &ntQueryVirtualMemory)) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x00"_Protect, GetLastError());
		return false;
	}

	NtQueryVirtualMemorySyscall = reinterpret_cast<tNtQueryVirtualMemory>(VirtualAlloc(NULL, 11, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
	if (!NtQueryVirtualMemorySyscall) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x01"_Protect, GetLastError());
		return false;
	}

	memcpy((void*)NtQueryVirtualMemorySyscall, syscallAsm, 11);
	*(int*)((DWORD64)NtQueryVirtualMemorySyscall + 4) = ntQueryVirtualMemory;

	//NtQueryInformationProcess
	int ntQueryInformationProcess = 0;
	if (!pMemory.GetSyscall(GetModuleHandleA("ntdll.dll"_Protect), 512, &ntQueryInformationProcess)) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x02"_Protect, GetLastError());
		return false;
	}

	NtQueryInformationProcessSyscall = reinterpret_cast<tNtQueryInformationProcess>(VirtualAlloc(NULL, 11, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
	if (!NtQueryInformationProcessSyscall) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x03"_Protect, GetLastError());
		return false;
	}

	memcpy((void*)NtQueryInformationProcessSyscall, syscallAsm, 11);
	*(int*)((DWORD64)NtQueryInformationProcessSyscall + 4) = ntQueryInformationProcess;

	//NtRaiseHardError
	int ntRaiseHardError = 0;
	if (!pMemory.GetSyscall(GetModuleHandleA("ntdll.dll"_Protect), 512, &ntRaiseHardError)) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x04"_Protect, GetLastError());
		return false;
	}

	NtRaiseHardErrorSyscall = reinterpret_cast<tNtRaiseHardError>(VirtualAlloc(NULL, 11, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
	if (!NtRaiseHardErrorSyscall) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x05"_Protect, GetLastError());
		return false;
	}

	memcpy((void*)NtRaiseHardErrorSyscall, syscallAsm, 11);
	*(int*)((DWORD64)NtRaiseHardErrorSyscall + 4) = ntRaiseHardError;

	//NtQuerySystemInformation
	int ntQuerySystemInformation = 0;
	if (!pMemory.GetSyscall(GetModuleHandleA("ntdll.dll"_Protect), 512, &ntQuerySystemInformation)) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x06"_Protect, GetLastError());
		return false;
	}

	NtQuerySystemInformationSyscall = reinterpret_cast<tNtQuerySystemInformation>(VirtualAlloc(NULL, 11, MEM_COMMIT, PAGE_EXECUTE_READWRITE));
	if (!NtQuerySystemInformationSyscall) {
		LOG_PUBLIC("Startup error: 0x%llx || 0x07"_Protect, GetLastError());
		return false;
	}

	memcpy((void*)NtQuerySystemInformationSyscall, syscallAsm, 11);
	*(int*)((DWORD64)NtQuerySystemInformationSyscall + 4) = ntQuerySystemInformation;

	//check if using test signing mode 
	SYSTEM_CODEINTEGRITY_INFORMATION Integrity = { sizeof(SYSTEM_CODEINTEGRITY_INFORMATION), 0 };
	NTSTATUS status = NtQuerySystemInformationSyscall(103, &Integrity, sizeof(Integrity), NULL);
	if ((NT_SUCCESS(status) && (Integrity.CodeIntegrityOptions & 1))) {
		pUtils.CloseProc("Testcode siging policy is active breaching the security integity of perplex services."_Protect);
		return false;
	}

	LOG_DEV("Security startup success!");

	ZeroMemory((void*)syscallAsm, strlen(syscallAsm));
	bSecurityStartupSuccess = true;
	return true;
}

bool Security::Initialize() {

	if (!bSecurityStartupSuccess) {
		BSOD();
		pUtils.CloseProc(":("_Protect);
	}

	NtQueryInformationProcess = reinterpret_cast<tNtQueryInformationProcess>(GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "NtQueryInformationProcess"_Protect));
	if (!NtQueryInformationProcess) {
		LOG_PUBLIC("Failed to find S_1"_Protect);
		return false;
	}

	RtlAdjustPrivilege = reinterpret_cast<tRtlAdjustPrivilege>(GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "RtlAdjustPrivilege"_Protect));
	if (!RtlAdjustPrivilege) {
		LOG_PUBLIC("Failed to find S_2"_Protect);
		return false;
	}

	NtRaiseHardError = reinterpret_cast<tNtRaiseHardError>(GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "NtRaiseHardError"_Protect));
	if (!NtRaiseHardError) {
		LOG_PUBLIC("Failed to find S_3"_Protect);
		return false;
	}

	NtQueryObject = reinterpret_cast<tNtQueryObject>(GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "NtQueryObject"_Protect));
	if (!NtQueryObject) {
		LOG_PUBLIC("Failed to find S_4"_Protect);
		return false;
	}

	NtQuerySystemInformation = reinterpret_cast<tNtQuerySystemInformation>(GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "NtQuerySystemInformation"_Protect));
	if (!NtQuerySystemInformation) {
		LOG_PUBLIC("Failed to find S_5"_Protect);
		return false;
	}

	NtSetInformationThread = reinterpret_cast<tNtSetInformationThread>(GetProcAddress(GetModuleHandleA("ntdll.dll"_Protect), "NtSetInformationThread"_Protect));
	if (!NtSetInformationThread) {
		LOG_PUBLIC("Failed to find S_6"_Protect);
		return false;
	}

	//WinHttpCrackUrl
	WinHttpCrackUrl = reinterpret_cast<tWinHttpCrackUrl>(GetProcAddress(GetModuleHandleA("winhttp.dll"_Protect), "WinHttpCrackUrl"_Protect));
	if (!WinHttpCrackUrl) {
		LOG_PUBLIC("Failed to find S_7"_Protect);
		return false;
	}

	//WinHttpCreateUrl
	WinHttpCreateUrl = reinterpret_cast<tWinHttpCreateUrl>(GetProcAddress(GetModuleHandleA("winhttp.dll"_Protect), "WinHttpCreateUrl"_Protect));
	if (!WinHttpCreateUrl) {
		LOG_PUBLIC("Failed to find S_8"_Protect);
		return false;
	}

	//WinHttpCreateUrl
	/*FindUrlComponents = reinterpret_cast<tFindUrlComponents>(GetProcAddress(GetModuleHandleA("winhttp.dll"_Protect), "FindUrlComponents"_Protect));
	if (!FindUrlComponents) {
		LOG_PUBLIC("Failed to find S_9"_Protect);
		return false;
	}*/

	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&NtQueryInformationProcess)), 0x4C);
	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&RtlAdjustPrivilege)), 0x48);
	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&NtRaiseHardError)), 0x4C);
	//RegisterFunctionIntegrity((void*)*(uint64_t*)(&NtQueryObject), 0x4C);
	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&NtQuerySystemInformation)), 0x4C);
	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&NtSetInformationThread)), 0x4C);

	/*winhttp*/
	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&WinHttpCrackUrl)), 0x00, true);
	RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&WinHttpCreateUrl)), 0x00, true);
	//RegisterFunctionIntegrity(reinterpret_cast<void*>(*reinterpret_cast<uint64_t*>(&FindUrlComponents)), 0x48);

	/*scylla*/
	RegisterFunctionIntegrity(&OutputDebugStringA, 0x48);
	RegisterFunctionIntegrity(&GetTickCount, 0xB9);
	RegisterFunctionIntegrity(&GetTickCount64, 0x8B);
	//RegisterFunctionIntegrity(&GetSystemTime, 0x48);
	RegisterFunctionIntegrity(&BlockInput);
	/*scylla*/

	RegisterFunctionIntegrity(&IsDebuggerPresent, 0x48);
	RegisterFunctionIntegrity(&CheckRemoteDebuggerPresent, 0x48);
	RegisterFunctionIntegrity(&CreateThread, 0x4C);
	RegisterFunctionIntegrity(&CloseHandle, 0xFF);
	RegisterFunctionIntegrity(&CreateToolhelp32Snapshot, 0x89);
	RegisterFunctionIntegrity(&exit, 0x45);
	RegisterFunctionIntegrity(&TerminateProcess, 0x48);
	RegisterFunctionIntegrity(&TerminateThread, 0x48);
	RegisterFunctionIntegrity(&GetProcAddress, 0x4C);
	RegisterFunctionIntegrity(&GetCurrentProcess, 0xFF);
	//RegisterFunctionIntegrity(&LoadLibraryA, 0x48);
	//RegisterFunctionIntegrity(&LoadLibraryW, 0x48);
	//RegisterFunctionIntegrity(&GetModuleHandleA, 0x48);
	//RegisterFunctionIntegrity(&GetModuleHandleW, 0x48);


	ImageSection section = pUtils.GetTextSection(pBackend.hMyModuleHandle, pBackend.MyPEHeader);
	TextSectionHash = sha256b(reinterpret_cast<BYTE*>(section.dwPointer), section.dwSize - 1);

	LOG_DEV("Section Hash: %s", TextSectionHash.c_str());

	pThreadPool.RegisterThread("S1"_Protect, [] { pSecurity.WatchMessengerPing(); });
	pThreadPool.RegisterThread("S2"_Protect, [] { pSecurity.WatchDebuggers(); });
	pThreadPool.RegisterThread("S3"_Protect, [] { pSecurity.WatchFunctionIntegrity(); });
	pThreadPool.RegisterThread("S4"_Protect, [] { pSecurity.WatchMemoryIntegrity(); });
	pThreadPool.RegisterThread("S5"_Protect, [] { pSecurity.WatchInternetConnection(); });
	pThreadPool.RegisterThread("S6"_Protect, [] { pSecurity.WatchThreadBP(); }); 
	pThreadPool.RegisterThread("S7"_Protect, [] { pSecurity.WatchProcesses(); });
	return true;
}

void Security::RegisterFunctionIntegrity(void* address, BYTE expectedFirstByte, bool HookChecked) {
	static int index = 0;
	index++;

	FunctionIntegrity integrity = FunctionIntegrity();
	integrity.iIndex = index;
	integrity.dwAddress = reinterpret_cast<uint64_t>(address);
	integrity.bHookCheck = HookChecked;

	if (address != nullptr) {
		if (expectedFirstByte != 0) {
			if (*static_cast<BYTE*>(address) != expectedFirstByte) {
				LOG_DEV("Function 0x%llx doesn't match expected byte %02x v %02x", address, *static_cast<BYTE*>(address), expectedFirstByte);
				pUtils.CloseProc("Integrity Building"_Protect);
				return;
			}
		}

		memcpy(integrity.szOriginalBytes, address, 5);
		IntegrityDatabase.push_back(integrity);

		LOG_DEV("Registered function with index of %i for integrity checking 0x%llx", index, address);
	}
}

void Security::WatchFunctionIntegrity() {
	for (auto& table : IntegrityDatabase) {
		if (table.bHookCheck) {
			if (*reinterpret_cast<BYTE*>(table.dwAddress) == 0xE9) {
				LOG_PUBLIC("Hook detected, rude..."_Protect);
				ProcessMetric(new MetricFunctionIntegrity());
				break;
			}
		}

		if (memcmp((void*)table.dwAddress, (void*)table.szOriginalBytes, 1)) {
			LOG_PUBLIC("A function has been modified - cut it out!"_Protect);
			ProcessMetric(new MetricFunctionIntegrity());
			break;
		}
	}

	Sleep(2000);
}

void Security::WatchInternetConnection() {
	bool bIsInternetAvailable = false;
	DWORD dwBufferSize = 0;

	if (ERROR_INSUFFICIENT_BUFFER == GetIpForwardTable(nullptr, &dwBufferSize, false)) {
		BYTE *pByte = new BYTE[dwBufferSize];
		if (pByte) {
			PMIB_IPFORWARDTABLE pRoutingTable = reinterpret_cast<PMIB_IPFORWARDTABLE>(pByte);
			if (NO_ERROR == GetIpForwardTable(pRoutingTable, &dwBufferSize, false)) {
				DWORD dwRowCount = pRoutingTable->dwNumEntries;
				for (DWORD dwIndex = 0; dwIndex < dwRowCount; ++dwIndex) {
					if (pRoutingTable->table[dwIndex].dwForwardDest == 0) {
						bIsInternetAvailable = true;
						break;
					}
				}
			}
			delete[] pByte;
		}
	}

	if (!bIsInternetAvailable) {
		pUtils.CloseProc("Your computer lost connection to the perplex servers"_Protect);
		return;
	}

	if (!bSecurityStartupSuccess) {
		BSOD();
		pUtils.CloseProc(":("_Protect);
	}

	Sleep(2000);
}

void Security::WatchMessengerPing() {
	static bool first = true;
	if (first) {
		first = false;
		Sleep(70000);
	}

	if (pMessenger.dwLastPing && GetTickCount() - pMessenger.dwLastPing > 20000) {
		// ping runs every 5 seconds, give it 2 seconds leeway
		pUtils.CloseProc("Ping timeout"_Protect);
		return;
	}

	Sleep(5000);
}

void Security::WatchDebuggers() {
	while (true) {
		_PEB_T* pPEB = (_PEB_T*)__readgsqword(0x60);

		if (pPEB->BeingDebugged) {
			LOG_PUBLIC("Debugging is not permitted"_Protect);
			ProcessMetric(new MetricDebuggerPresent());
		}

		if (pPEB->NtGlobalFlag & 0x70) {
			LOG_PUBLIC("Debugging is not permitted"_Protect);
			ProcessMetric(new MetricDebuggerPresent());
		}

		auto heaps = (void**)pPEB->ProcessHeaps;
		for (DWORD i = 0; i < pPEB->NumberOfHeaps; i++) {
			auto flags = *(DWORD*)((BYTE*)heaps[i] + 0x70);
			auto force_flags = *(DWORD*)((BYTE*)heaps[i] + 0x74);
			auto bad_flags = 0x00000020 | 0x00000040 | 0x10000000 | 0x40000000;

			if ((flags & bad_flags) || (force_flags & bad_flags)) {
				LOG_PUBLIC("Debugging is not permitted"_Protect);
				ProcessMetric(new MetricDebuggerPresent());
				break;
			}
		}

		auto rupp = (RTL_USER_PROCESS_PARAMETERS*)pPEB->ProcessParameters;
		if (rupp->Flags & 0x4000 == 0) {
			LOG_PUBLIC("Debugging is not permitted"_Protect);
			ProcessMetric(new MetricDebuggerPresent());
		}

		if (IsDebuggerPresent()) {
			LOG_PUBLIC("Debugging is not permitted"_Protect);
			ProcessMetric(new MetricDebuggerPresent());
		}

		BOOL present;
		CheckRemoteDebuggerPresent(GetCurrentProcess(), &present);

		if (present) {
			LOG_PUBLIC("Debugging is not permitted"_Protect);
			ProcessMetric(new MetricDebuggerPresent());
		}

		HANDLE handle = nullptr;

		if (!NtQueryInformationProcessSyscall(GetCurrentProcess(), 7, &handle, sizeof(handle), nullptr)) {
			if (handle) {
				LOG_PUBLIC("Debugging is not permitted"_Protect);
				ProcessMetric(new MetricDebuggerPresent());
			}
		}

		if (!NtQueryInformationProcessSyscall(GetCurrentProcess(), 30, handle, sizeof(HANDLE), nullptr)) {
			if (handle) {
				LOG_PUBLIC("Debugging is not permitted"_Protect);
				ProcessMetric(new MetricDebuggerPresent());
			}
		}

		SYSTEM_KERNEL_DEBUGGER_INFORMATION SysKernDebInfo;
		if (!NtQuerySystemInformationSyscall(35, &SysKernDebInfo, sizeof(SysKernDebInfo), NULL)) {
			if (SysKernDebInfo.KernelDebuggerEnabled || !SysKernDebInfo.KernelDebuggerNotPresent) {
				LOG_PUBLIC("Debugging is not permitted"_Protect);
				ProcessMetric(new MetricDebuggerPresent());
			}
		}

		SYSTEM_CODEINTEGRITY_INFORMATION Integrity = { sizeof(SYSTEM_CODEINTEGRITY_INFORMATION), 0 };
		NTSTATUS status = NtQuerySystemInformationSyscall(103, &Integrity, sizeof(Integrity), NULL);
		if ((NT_SUCCESS(status) && (Integrity.CodeIntegrityOptions & 1))) {
			LOG_PUBLIC("Testcode siging policy is active breaching the security integity of perplex services."_Protect);
			BSOD();
		}

		Sleep(5000);
	}
}

void Security::WatchMemoryIntegrity() {
	while (true) {
		ImageSection section = pUtils.GetTextSection(pBackend.hMyModuleHandle, pBackend.MyPEHeader);
		auto currentHash = sha256b(reinterpret_cast<BYTE*>(section.dwPointer), section.dwSize - 1);

		if (currentHash.compare(TextSectionHash)) {
			// text section modified, send metric
			LOG_DEV("Memory integrity changed");
			ProcessMetric(new MetricMemoryIntegrity());
		}

#ifndef DEBUG
		if (!VMProtectIsValidImageCRC()) {
			ProcessMetric(new MetricMemoryIntegrity());
	}
#endif

		Sleep(5000);
}
}

void Security::WatchThreadBP() {
	while (true) {
		auto threads = pThreadPool.GetThreads();

		for (auto& thread : threads) {
			if (thread->GetHandle()) {
				CONTEXT cxt = { 0 };
				cxt.ContextFlags = CONTEXT_DEBUG_REGISTERS;

				if (GetThreadContext(thread->GetHandle(), &cxt) == 0)
					continue;

				if (cxt.Dr0 != 0 || cxt.Dr1 != 0 || cxt.Dr2 != 0 || cxt.Dr3 != 0) {
					// thread is being debugged, send metric
					LOG_PUBLIC("Debugging is not permitted"_Protect);
					ProcessMetric(new MetricDebuggerPresent());
					break;
				}
			}
		}

		Sleep(5000);
	}
}

void Security::WatchProcesses() {
	while (true) {
#ifndef DEBUG
		if (pUtils.IsProcessRunning("cheatengine"_Protect) ||
			pUtils.IsProcessRunning("x64dbg"_Protect) ||
			pUtils.IsProcessRunning("cheatengine-x86_64"_Protect) ||
			pUtils.IsProcessRunning("debugger"_Protect) ||
			pUtils.IsProcessRunning("wireshark"_Protect)) {
			pUtils.CloseProc("Blacklisted process"_Protect);
		}
		Sleep(2000);
#endif
	}
}

void Security::WatchHandles() {

}

bool Security::DisablePerplex() {

}