#pragma once

/*Generic*/
#define STATUS_SUCCESS				(0x000u)
#define STATUS_NOTHING				(0x001u)
#define STATUS_FATAL				(0x002u)
#define STATUS_WARNING				(0x003u)
#define STATUS_UNKNOWN				(0x004u)
#define STATUS_ALREADYINITIALIZED	(0x005u)

extern bool gIsHooking;

typedef struct _PEB_LDR_DATA {
	UINT8 _PADDING_[12];
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

#pragma pack(push, 1)
struct _PEB_T {
	union {
		struct {
			BYTE InheritedAddressSpace;
			BYTE ReadImageFileExecOptions;
			BYTE BeingDebugged;
			BYTE _SYSTEM_DEPENDENT_01;
		};
		DWORD64 dummy01;
	};
	DWORD64 Mutant;
	DWORD64 ImageBaseAddress;
	PEB_LDR_DATA* Ldr;
	DWORD64 ProcessParameters;
	DWORD64 SubSystemData;
	DWORD64 ProcessHeap;
	DWORD64 FastPebLock;
	DWORD64 _SYSTEM_DEPENDENT_02;
	DWORD64 _SYSTEM_DEPENDENT_03;
	DWORD64 _SYSTEM_DEPENDENT_04;
	union {
		DWORD64 KernelCallbackTable;
		DWORD64 UserSharedInfoPtr;
	};
	DWORD SystemReserved;
	DWORD _SYSTEM_DEPENDENT_05;
	DWORD64 _SYSTEM_DEPENDENT_06;
	DWORD64 TlsExpansionCounter;
	DWORD64 TlsBitmap;
	DWORD TlsBitmapBits[2];
	DWORD64 ReadOnlySharedMemoryBase;
	DWORD64 _SYSTEM_DEPENDENT_07;
	DWORD64 ReadOnlyStaticServerData;
	DWORD64 AnsiCodePageData;
	DWORD64 OemCodePageData;
	DWORD64 UnicodeCaseTableData;
	DWORD NumberOfProcessors;
	union {
		DWORD NtGlobalFlag;
		DWORD dummy02;
	};
	LARGE_INTEGER CriticalSectionTimeout;
	DWORD64 HeapSegmentReserve;
	DWORD64 HeapSegmentCommit;
	DWORD64 HeapDeCommitTotalFreeThreshold;
	DWORD64 HeapDeCommitFreeBlockThreshold;
	DWORD NumberOfHeaps;
	DWORD MaximumNumberOfHeaps;
	DWORD64 ProcessHeaps;
	DWORD64 GdiSharedHandleTable;
	DWORD64 ProcessStarterHelper;
	DWORD64 GdiDCAttributeList;
	DWORD64 LoaderLock;
	DWORD OSMajorVersion;
	DWORD OSMinorVersion;
	WORD OSBuildNumber;
	WORD OSCSDVersion;
	DWORD OSPlatformId;
	DWORD ImageSubsystem;
	DWORD ImageSubsystemMajorVersion;
	DWORD64 ImageSubsystemMinorVersion;
	union {
		DWORD64 ImageProcessAffinityMask;
		DWORD64 ActiveProcessAffinityMask;
	};
	DWORD64 GdiHandleBuffer[30];
	DWORD64 PostProcessInitRoutine;
	DWORD64 TlsExpansionBitmap;
	DWORD TlsExpansionBitmapBits[32];
	DWORD64 SessionId;
	ULARGE_INTEGER AppCompatFlags;
	ULARGE_INTEGER AppCompatFlagsUser;
	DWORD64 pShimData;
	DWORD64 AppCompatInfo;
	UNICODE_STRING CSDVersion;
	DWORD64 ActivationContextData;
	DWORD64 ProcessAssemblyStorageMap;
	DWORD64 SystemDefaultActivationContextData;
	DWORD64 SystemAssemblyStorageMap;
	DWORD64 MinimumStackCommit;
};

struct CURDIR {
	UNICODE_STRING DosPath;
	DWORD_PTR Handle;
};

typedef struct _SYSTEM_KERNEL_DEBUGGER_INFORMATION {
	BOOLEAN KernelDebuggerEnabled;
	BOOLEAN KernelDebuggerNotPresent;
} SYSTEM_KERNEL_DEBUGGER_INFORMATION, *PSYSTEM_KERNEL_DEBUGGER_INFORMATION;

struct RTL_USER_PROCESS_PARAMETERS {
	ULONG MaximumLength;
	ULONG Length;

	ULONG Flags;
	ULONG DebugFlags;

	DWORD_PTR ConsoleHandle;
	ULONG  ConsoleFlags;
	DWORD_PTR StandardInput;
	DWORD_PTR StandardOutput;
	DWORD_PTR StandardError;

	CURDIR CurrentDirectory;
	UNICODE_STRING DllPath;
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
	DWORD_PTR Environment;

	ULONG StartingX;
	ULONG StartingY;
	ULONG CountX;
	ULONG CountY;
	ULONG CountCharsX;
	ULONG CountCharsY;
	ULONG FillAttribute;

	ULONG WindowFlags;
	ULONG ShowWindowFlags;
	UNICODE_STRING WindowTitle;
	UNICODE_STRING DesktopInfo;
	UNICODE_STRING ShellInfo;
	UNICODE_STRING RuntimeData;
};

struct LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	WORD LoadCount;
	WORD TlsIndex;
	union {
		LIST_ENTRY HashLinks;
		struct {
			PVOID SectionPointer;
			ULONG CheckSum;
		};
	};
	union {
		ULONG TimeDateStamp;
		PVOID LoadedImports;
	};
	_ACTIVATION_CONTEXT * EntryPointActivationContext;
	PVOID PatchInformation;
	LIST_ENTRY ForwarderLinks;
	LIST_ENTRY ServiceTagLinks;
	LIST_ENTRY StaticLinks;
};
#pragma pack(pop)

#define UNLINK(x)                   \
    (x).Flink->Blink = (x).Blink;   \
    (x).Blink->Flink = (x).Flink;
#define RELINK(x, real)         \
    (x).Flink->Blink = (real);  \
    (x).Blink->Flink = (real);  \
    (real)->Blink = (x).Blink;  \
    (real)->Flink = (x).Flink;
#define DUMMYLINK(x, fake) \
	(x).Flink->Blink = (fake).Flink->Blink; \
	(x).Blink->Flink = (fake).Blink->Flink; 

template<typename T>
inline uint64_t GetAddressFromInstruction(T address, int offset = 0, int opSize = 3, int opLength = 7) {
	T _address = (address + offset);
	return (uint64_t)(*reinterpret_cast<int*>(_address + opSize) + _address + opLength);
}

template<typename T>
inline T* SetAddressTypeForUse(DWORD64 address, int offset = 0) {
	return reinterpret_cast<T*>(reinterpret_cast<char*>(address) + offset);
}

template <typename T>
inline uint32_t IsValidAddress(T* address, string name, bool isImportant, int offsetted = 0, bool isPattern = true) {
	if ((address >= (PVOID)0x10000) && (address < ((PVOID)0x7fffffffffffffff)) && address != nullptr && !IsBadReadPtr(address, sizeof(address)) && address != (T*)offsetted) {
		if (isPattern) {
			LOG_DEV("Found %s", name.c_str());
		}

		return STATUS_SUCCESS;
	}

	if (isImportant) {
		LOG_DEV("Failed to find %s", name.c_str());
		return STATUS_FATAL;
	}

	LOG_DEV("Failed to find %s", name.c_str());
	return STATUS_WARNING;
}

inline bool ValidPtr(void* address) {
	if ((address >= (PVOID)0x10000) && (address < ((PVOID)0x7fffffffffffffff)) && address != nullptr && !IsBadReadPtr(address, sizeof(address))) {
		return true;
	}

	return false;
}

class Memory {
public:
	uint64_t Scan(const char* signature);
	const char *Stacktrace();
	BOOL GetSyscall(HMODULE hModule, int Ordinal, int* pSyscall);

	void FakePeHeader(HMODULE hModule) {
		void* pKernel32 = reinterpret_cast<void*>(GetModuleHandleA("kernel32.dll"));
		DWORD dwOriginal = 0;
		VirtualProtectEx(GetCurrentProcess(), hModule, 0x1000, PAGE_EXECUTE_READWRITE, &dwOriginal);
		WriteProcessMemory(GetCurrentProcess(), hModule, pKernel32, 0x1000, nullptr);
		VirtualProtectEx(GetCurrentProcess(), hModule, 0x1000, dwOriginal, &dwOriginal);
	}

	void UnlinkModuleFromPEB(HMODULE hModule) {
		_PEB_T* pPEB = (_PEB_T*)__readgsqword(0x60);

		PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
		LDR_DATA_TABLE_ENTRY* Current = NULL;

		while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL) {
			Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

			if (Current->DllBase == hModule) {
				UNLINK(Current->InLoadOrderLinks);
				UNLINK(Current->InInitializationOrderLinks);
				UNLINK(Current->InMemoryOrderLinks);
				break;
			}

			//dummy dll to 
			//memcpy(&mine->InLoadOrderLinks, &dummy->InLoadOrderLinks, sizeof(LIST_ENTRY) * 3)

			CurrentEntry = CurrentEntry->Flink;
		}
	}

	void LinkToDummyDLL(HMODULE hMyModule, HMODULE hDummyModule) {
		_PEB_T* pPEB = (_PEB_T*)__readgsqword(0x60);

		PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
		LDR_DATA_TABLE_ENTRY* Current = NULL;
		LDR_DATA_TABLE_ENTRY* MyModuleLDRTable = nullptr;
		LDR_DATA_TABLE_ENTRY* DummyModuleLDRTable = nullptr;

		while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL) {
			Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

			if (Current->DllBase == hMyModule) {
				MyModuleLDRTable = Current;
			} else if (Current->DllBase == hDummyModule) {
				DummyModuleLDRTable = Current;
			}

			if (DummyModuleLDRTable != nullptr && MyModuleLDRTable != nullptr) {
				DummyModuleLDRTable->SizeOfImage = 0xFFFFFFFF;
				MyModuleLDRTable->SizeOfImage = 0xFFFFFFFF;
				MyModuleLDRTable->DllBase = reinterpret_cast<PVOID>(reinterpret_cast<DWORD64>(GetModuleHandleA("socialclub.dll"_Protect) + 0x100));
				DummyModuleLDRTable->DllBase = reinterpret_cast<PVOID>(reinterpret_cast<DWORD64>(GetModuleHandleA("socialclub.dll"_Protect) + 0x200));
				LOG_DEV("Got LDR table for both modules!");
				break;
			}

			CurrentEntry = CurrentEntry->Flink;
		}

		if (DummyModuleLDRTable != nullptr && MyModuleLDRTable != nullptr) {
			UnlinkModuleFromPEB(hDummyModule);
			UnlinkModuleFromPEB(hMyModule);
			//DUMMYLINK(MyModuleLDRTable->InLoadOrderLinks, DummyModuleLDRTable->InLoadOrderLinks);
			//DUMMYLINK(MyModuleLDRTable->InInitializationOrderLinks, DummyModuleLDRTable->InInitializationOrderLinks);
			//DUMMYLINK(MyModuleLDRTable->InMemoryOrderLinks, DummyModuleLDRTable->InMemoryOrderLinks);
			//memcpy(MyModuleLDRTable->DllBase, DummyModuleLDRTable->DllBase, 0x8);
			//DUMMYLINK(MyModuleLDRTable->EntryPoint, DummyModuleLDRTable->EntryPoint);
			//strcpy(MyModuleLDRTable->DllPath, DummyModuleLDRTable->DllPath, sizeof(UNICODE_STRING));
		}
		//memcpy(&MyModuleLDRTable->InLoadOrderLinks, &DummyModuleLDRTable->InLoadOrderLinks, sizeof(LIST_ENTRY) * 3);
	}

	bool IsScanInOurMemory(uint64_t baseScan, uint64_t endScan, uint64_t moduleBase, uint64_t moduleEnd) {
		return pUtils.Within(baseScan, moduleBase, moduleEnd) || pUtils.Within(endScan, moduleBase, moduleEnd);
	}
	
	template<typename ValueType, typename AddressType>
	void Write(AddressType address, ValueType value) {
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template<typename AddressType>
	void WriteOffsets(AddressType address, vector<BYTE> offsets) {
		for (int i = 0; i < offsets.size(); i++) {
			DWORD oldProtect;
			auto value = offsets[i];
			VirtualProtect((void*)(address + i), sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

			memcpy((void*)(address + i), &value, sizeof(value));

			VirtualProtect((void*)(address + i), sizeof(value), oldProtect, &oldProtect);
		}
	}

	template<typename AddressType>
	void Nop(AddressType address, size_t length) {
		DWORD oldProtect;
		VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

		memset((void*)address, 0x90, length);

		VirtualProtect((void*)address, length, oldProtect, &oldProtect);
	}

	template<typename T>
	bool PatternCallback(PStruct pattern, function<void(T*)> funcptr) {
		T* address = SetAddressTypeForUse<char>(Scan(pattern.Pattern.c_str()), pattern.nOffset);
		switch (IsValidAddress<T>(address, pattern.Name, pattern.bImportant, pattern.nOffset)) {
		case STATUS_SUCCESS: funcptr(address); return true; break;
		case STATUS_WARNING: if (!pattern.bImportant) { return true; }
		case STATUS_FATAL: LOG_DEV("%s pattern callback failed", pattern.Name.c_str()); break;
		}
		return false;
	}

	template<typename T>
	bool PatternCallback(PStruct pattern, function<bool(T*)> funcptr) {
		T* address = SetAddressTypeForUse<char>(Scan(pattern.Pattern.c_str()), pattern.nOffset);
		switch (IsValidAddress<T>(address, pattern.Name, pattern.bImportant, pattern.nOffset)) {
		case STATUS_SUCCESS: if (funcptr(address)) return true; else if (pattern.bImportant) { LOG_DEV("%s pattern callback failed", pattern.Name.c_str()); } break;
		case STATUS_WARNING: if (!pattern.bImportant) { return true; }
		case STATUS_FATAL:  LOG_DEV("%s pattern callback failed", pattern.Name.c_str()); return false; break;
		}
		return false;
	}

	template<typename T>
	bool ManagerPatternCallback(AuthSignatures signature, function<void(T*)> funcptr) {
		T* address = SetAddressTypeForUse<char>(ResolvedSignatures[signature]);
		if (ValidPtr(address)) {
			funcptr(address);
			LOG_PUBLIC("Found %i", signature);
			return true;
		} else {
			LOG_PUBLIC("Failed to find %i", signature);
		}

		return false;
	}

	template<typename T>
	bool ManagerPatternCallback(AuthSignatures signature, function<bool(T*)> funcptr) {
		T* address = SetAddressTypeForUse<char>(ResolvedSignatures[signature]);

		if (ValidPtr(address)) {
			LOG_PUBLIC("Found %i\n", signature);
			return funcptr(address);
		}

		return false;
	}

	bool compare(const uint8_t* pData, const uint8_t* bMask, const char* sMask) {
		for (; *sMask; ++sMask, ++pData, ++bMask)
			if (*sMask == 'x' && *pData != *bMask)
				return false;
		return *sMask == NULL;
	}

	vector<DWORD64> GetStringAddress(string str) {
		MODULEINFO module;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module, sizeof(MODULEINFO));

		string currentMask;
		const char* to_scan = str.c_str();
		for (uint8_t i = 0; i < strlen(to_scan); i++) currentMask += "x";
		const char *mask = currentMask.c_str();
		vector<DWORD64> foundAddrs;
		for (uint32_t i = 0; i < module.SizeOfImage; ++i) {
			auto address = (DWORD64)module.lpBaseOfDll + i;
			if (compare((BYTE *)(address), (BYTE *)to_scan, mask)) {
				foundAddrs.push_back((address));
			}
		}

		return foundAddrs;
	}

	uintptr_t GetMultilayerPointer(uintptr_t base_address, std::vector<DWORD> offsets) {
		uintptr_t ptr = *(uintptr_t*)(base_address);
		if (!ptr) {
			return NULL;
		}
		auto level = offsets.size();

		for (auto i = 0; i < level; i++) {
			if (i == level - 1) {
				ptr += offsets[i];
				if (!ptr) return NULL;
				return ptr;
			} else {
				ptr = *(uint64_t*)(ptr + offsets[i]);
				if (!ptr) return NULL;
			}
		}
		return ptr;
	}

	bool IsBadPtr(void* address) {
		MEMORY_BASIC_INFORMATION mbi;
		if (VirtualQuery(address, &mbi, sizeof mbi)) {
			const DWORD mask = (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY);
			auto b = !(mbi.Protect & mask);
			// check the page is not a guard page
			if (mbi.Protect & (PAGE_GUARD | PAGE_NOACCESS)) {
				b = true;
			}

			return b;
		}
		return true;
	}
};

extern Memory pMemory;