#include "stdafx.h"

bool gIsHooking;

Memory pMemory;

struct PatternByte {
	PatternByte() : ignore(true) {
		//
	}

	PatternByte(string byteString, bool ignoreThis = false) {
		data = StringToUint8(byteString);
		ignore = ignoreThis;
	}

	bool ignore;
	UINT8 data;

private:
	UINT8 StringToUint8(string str) {
		istringstream iss(str);

		UINT32 ret;

		if (iss >> hex >> ret) {
			return (UINT8)ret;
		}

		return 0;
	}
};

uint64_t Memory::Scan(const char* signature) {
	MODULEINFO module;
	GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &module, sizeof(MODULEINFO));

	vector<PatternByte> p;
	istringstream iss(signature);
	string w;

	while (iss >> w) {
		if (w.data()[0] == '?') {
			p.push_back(PatternByte());
		} else if (w.length() == 2 && isxdigit(w.data()[0]) && isxdigit(w.data()[1])) { // Hex
			p.push_back(PatternByte(w));
		} else {
			return NULL;
		}
	}

	for (DWORD64 i = 0; i < (DWORD64)module.SizeOfImage; i++) {
		UINT8* lpCurrentByte = (UINT8*)((DWORD64)module.lpBaseOfDll + i);

		bool found = true;

		for (size_t ps = 0; ps < p.size(); ps++) {
			if (p[ps].ignore == false && lpCurrentByte[ps] != p[ps].data) {
				found = false;
				break;
			}
		}

		if (found) {
			return (DWORD64)lpCurrentByte;
		}
	}

	return NULL;
}

BOOL Memory::GetSyscall(HMODULE hModule, int Ordinal, int* pSyscall) {
	if (auto proc = GetProcAddress(hModule, MAKEINTRESOURCEA(Ordinal))) {
		uint64_t proc_ = (uint64_t)proc;
		if (*(BYTE*)proc_ == 0x4C) {
			// if the first byte is the byte for { mov r10, rcx } - the start of every syscall func
			*pSyscall = *(int*)(proc_ + 4);
			return TRUE;
		}
	}

	return FALSE;
}

typedef USHORT(WINAPI *CaptureStackBackTraceType)(__in ULONG, __in ULONG, __out PVOID*, __out_opt PULONG);
const char* Memory::Stacktrace() {
	std::string s("[");
	const auto captureStacktrace = reinterpret_cast<CaptureStackBackTraceType>(GetProcAddress(LoadLibraryA("kernel32.dll"), "RtlCaptureStackBackTrace"));

	if (captureStacktrace != nullptr)
	{
		HMODULE hMods[1024];
		DWORD cbNeeded;

		EnumProcessModules(HANDLE(-1), hMods, sizeof hMods, &cbNeeded);

		const auto kMaxCallers = 62;
		void* callers[kMaxCallers];
		const int count = (captureStacktrace)(0, kMaxCallers, callers, nullptr);

		for (auto i = 1; i < count; i++)
		{
			const auto callerAddress = DWORD64(callers[i]);
			HMODULE currentCallerModule = nullptr;

			for (unsigned int i2 = 0; i2 < cbNeeded / sizeof(HMODULE); i2++)
			{
				MODULEINFO information;

				GetModuleInformation(HANDLE(-1), hMods[i2], &information, sizeof information);

				if (callerAddress >= DWORD64(information.lpBaseOfDll) && callerAddress <= DWORD64(information.lpBaseOfDll) + information.SizeOfImage)
				{
					currentCallerModule = hMods[i2];
					break;
				}
			}
			if (currentCallerModule != nullptr) {
				char moduleName[MAX_PATH];
				GetModuleBaseNameA(HANDLE(-1), currentCallerModule, moduleName, MAX_PATH);
				char buf[512];
				sprintf_s(buf, "0x%08llx (%s)%s", callerAddress - DWORD64(currentCallerModule), moduleName, i != count - 1 ? ", " : "");
				s += buf;
			}
			else
			{
				char buf[512];
				sprintf_s(buf, "0x%016llx %s", callerAddress, i != count - 1 ? ", " : "");
				s += buf;
			}
		}

		s += "]";
		return s.c_str();
	}

	return "Stacktrace failed";
}