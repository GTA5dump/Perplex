#pragma once

typedef int(*tNtQueryInformationProcess)(HANDLE, UINT, PVOID, ULONG, PULONG);
typedef NTSTATUS(*tRtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
typedef NTSTATUS(*tNtRaiseHardError)(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
typedef NTSTATUS(*tNtQueryObject)(HANDLE ObjectHandle, ULONG ObjectInformationClass, PVOID ObjectInformation, ULONG ObjectInformationLength, PULONG ReturnLength);
typedef NTSTATUS(*tNtQuerySystemInformation)(ULONG, PVOID, ULONG, PULONG);
typedef NTSTATUS(*tNtSetInformationThread)(HANDLE thread, UINT type, PVOID unk1, DWORD unk2);
typedef NTSTATUS(*tNtQueryVirtualMemory)(HANDLE, PVOID, MEMORY_INFORMATION_CLASS, PVOID, SIZE_T, PSIZE_T);

typedef BOOL(__stdcall* tWinHttpCrackUrl)(LPCWSTR pwszUrl, DWORD dwUrlLength, DWORD dwFlags, LPURL_COMPONENTS lpUrlComponents);
typedef BOOL(__stdcall* tWinHttpCreateUrl)(LPURL_COMPONENTS lpUrlComponents, DWORD dwFlags, LPWSTR pwszUrl, LPDWORD pdwUrlLength);
typedef long(*tFindUrlComponents)(int, unsigned short const*, int, int, struct tagProxyResolveUrl**);


struct FunctionIntegrity {
	int iIndex;
	bool bHookCheck;
	uint64_t dwAddress;
	BYTE szOriginalBytes[5];
};

struct SYSTEM_CODEINTEGRITY_INFORMATION {
	ULONG Length;
	ULONG CodeIntegrityOptions;
};

class Security {
public:
	bool StartUp();
	bool Initialize();
	void BSOD();
	void BanUser();
	void RegisterFunctionIntegrity(void* address, BYTE expectedFirstByte = 0, bool HookChecked = false);

	// threads
	void WatchMessengerPing();
	void WatchDebuggers();
	void WatchFunctionIntegrity();
	void WatchMemoryIntegrity();
	void WatchInternetConnection();
	void WatchThreadBP();
	void WatchProcesses();
	void WatchHandles();


	bool DisablePerplex();

	bool bSecurityStartupSuccess;

	vector<FunctionIntegrity> IntegrityDatabase;
	string TextSectionHash;

	//winhttp defines
	tWinHttpCrackUrl WinHttpCrackUrl;
	tWinHttpCreateUrl WinHttpCreateUrl;
	tFindUrlComponents FindUrlComponents;

	// nt defines
	tNtQueryInformationProcess NtQueryInformationProcess;
	tRtlAdjustPrivilege RtlAdjustPrivilege;
	tNtRaiseHardError NtRaiseHardError;
	tNtQueryObject NtQueryObject;
	tNtQuerySystemInformation NtQuerySystemInformation;
	tNtSetInformationThread NtSetInformationThread;

	//syscall
	tNtQueryVirtualMemory NtQueryVirtualMemorySyscall;
	tNtQueryInformationProcess NtQueryInformationProcessSyscall;
	tNtQuerySystemInformation NtQuerySystemInformationSyscall;
	tNtRaiseHardError NtRaiseHardErrorSyscall;
};

extern Security pSecurity;