#include "stdafx.h"

Utils pUtils;
unordered_map<AuthSignatures, uint64_t> ResolvedSignatures;

void Utils::CloseProc(string error) {
	LOG_PUBLIC(error.c_str());
	LOG_PUBLIC("Closing process!"_Protect);

	if (!error.empty()) {
		ShellExecute(NULL, L"open", CharToWCHART(cprintf("%s/ErrorHandler.exe"_Protect, pConfig.GetPerplexGTARootPath().c_str())), CharToWCHART(pEncryption.base64_encode(error.c_str()).c_str()), NULL, SW_SHOWDEFAULT);
	}

	TerminateProcess(GetCurrentProcess(), 0);
	exit(0);
	system("taskkill /F /T /IM GTA5.exe"_Protect);
}

void Utils::DisplayMessageBox(const char* messagebox) {
	MessageBoxA(NULL, messagebox, "Message", MB_SYSTEMMODAL);
}

BOOL CALLBACK EnumWindowsCallback(HWND hWnd, LPARAM lParam) {
	HandleData& data = *(HandleData*)lParam;
	DWORD pid = 0;
	GetWindowThreadProcessId(hWnd, &pid);
	if (pid == data.pid && GetWindow(hWnd, GW_OWNER) == HWND(0) && IsWindowVisible(hWnd)) {
		data.hWnd = hWnd;
		return FALSE;
	}

	return TRUE;
}

HWND Utils::FindMainWindow(DWORD dwPID) {
	HandleData handleData{ 0 };
	handleData.pid = dwPID;
	EnumWindows(EnumWindowsCallback, (LPARAM)&handleData);
	return handleData.hWnd;
}

ImageSection Utils::GetTextSection(HMODULE hModule, vector<char> originalPE) {
	ImageSection output = {};

	PIMAGE_DOS_HEADER pDOSHeader = nullptr;
	PIMAGE_NT_HEADERS pNTHeader = nullptr;

	if (originalPE.empty()) {
		pDOSHeader = static_cast<PIMAGE_DOS_HEADER>(static_cast<PVOID>(hModule));
		pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<PBYTE>(hModule) + pDOSHeader->e_lfanew);
	} else {
		pDOSHeader = static_cast<PIMAGE_DOS_HEADER>(static_cast<PVOID>(originalPE.data()));
		pNTHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<PBYTE>(originalPE.data()) + pDOSHeader->e_lfanew);
	}

	IMAGE_SECTION_HEADER *pSectionHeader = reinterpret_cast<IMAGE_SECTION_HEADER*>(pNTHeader + 1);
	for (int i = 0; i < pNTHeader->FileHeader.NumberOfSections; i++) {
		const char* section = reinterpret_cast<char*>(pSectionHeader->Name);
		uint64_t start = reinterpret_cast<uint64_t>(hModule) + pSectionHeader->VirtualAddress;

		if (!strcmp(section, ".text")) {
			output.dwPointer = start;
			output.dwSize = pSectionHeader->Misc.VirtualSize;
			break;
		}

		pSectionHeader += 1;
	}

	return output;
}

vector<string> Utils::ResolveFileNamesFromFolder(string folder, string extension, int removeFromEndChars) {
	vector<string> files;

	string loc = folder + extension;
	WIN32_FIND_DATAA fd;
	HANDLE hFind = ::FindFirstFileA(loc.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				string orig = fd.cFileName;
				string newstring = orig.substr(0, orig.size() - removeFromEndChars);
				files.push_back(newstring);
			}
		} while (::FindNextFileA(hFind, &fd));
		::FindClose(hFind);
	}

	return files;
}

/*
	wcstombs(EncryptedBuffer, wstring, sizeof(EncryptedBuffer));
	auto decrypt = VMProtectDecryptStringA(EncryptedBuffer);
	const size_t cSize = strlen(decrypt) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, decrypt, cSize);
	ZeroMemory(EncryptedBuffer, sizeof(EncryptedBuffer));
*/
char ProcessRunningBuffer[100];
bool Utils::IsProcessRunning(const char* processName) {
	bool exists = false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry)) {
		while (Process32Next(snapshot, &entry)) {
			wcstombs(ProcessRunningBuffer, entry.szExeFile, sizeof(ProcessRunningBuffer));
			if (strstr(ProcessRunningBuffer, processName)) {
				exists = true;
			}
			ZeroMemory(ProcessRunningBuffer, sizeof(ProcessRunningBuffer));
		}
	}

	CloseHandle(snapshot);
	return exists;
}

vector<string> Utils::Split(const char *str, char c) {
	vector<string> result;

	do {
		const char *begin = str;

		while (*str != c && *str)
			str++;

		result.push_back(string(begin, str));
	} while (0 != *str++);

	return result;
}

char cprintfBuffer[0x1000];
const char* Utils::cprintf(const char* format, ...) {
	ZeroMemory(cprintfBuffer, 0x1000);
	va_list ap;
	va_start(ap, format);
	vsprintf_s(cprintfBuffer, format, ap);
	va_end(ap);
	return cprintfBuffer;
}

void Utils::VABuffer(char* buffer, int bufferSize, const char* format, ...) {
	ZeroMemory(buffer, bufferSize);
	va_list ap;
	va_start(ap, format);
	vsprintf(buffer, format, ap);
	va_end(ap);
}

bool Utils::IsValidJSONResponse(string json) {
	return (json.at(0) == '{' && json.at(json.size() - 1) == '}' && json != "{}");
}

bool Utils::DoesStingHaveInvalidChars(string input) {
	//return (isascii(input.c_str()));
	for (int i = 0; i < input.length(); i++) {
		if (!isascii(input[i]) && !isprint(input[i])) {
			return true;
		}
	}
	return false;
}

wchar_t *Utils::CharToWCHART(const char* charArray) {
	wchar_t* wString = nullptr;
	size_t size = strlen(charArray);

	if (wString != nullptr) {
		delete[] wString;
	}

	wString = new wchar_t[size];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, size);
	return wString;
}


static const char charmap[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
string Utils::GenerateRandomString(int length) {
	string result;
	srand(time(0));
	for (int i = 0; i < length; i++) {
		result += charmap[(rand() % (sizeof(charmap) - 1) + 1)];
	}
	return result;
}

void Utils::RunTimedFunction(int* timer, int ms, function<void()> function) {
	if (*timer < GetGameTimer()) {
		*timer = GetGameTimer() + ms;
		function();
	}
}

void Utils::GetCameraDirection(float *dirX, float *dirY, float *dirZ, Vector3 rotation) {
	float tX, tZ, num;
	Vector3 rot;
	if (rotation == Vector3())
		rot = CAM::GetGameplayCamRot(0);
	else
		rot = rotation;

	tZ = rot.z * 0.0174532924f;
	tX = rot.x * 0.0174532924f;
	num = abs(cos(tX));

	*dirX = (-sin(tZ)) * num;
	*dirY = (cos(tZ)) * num;
	*dirZ = sin(tX);
}

Vector3 Utils::RotateToDirection(Vector3*rot) {
	float radiansZ = rot->z * 0.0174532924f;
	float radiansX = rot->x * 0.0174532924f;
	float num = abs(static_cast<float>(cos(static_cast<double>(radiansX))));

	Vector3 ret_dir = {
		(float)((double)((float)(-(float)sin((double)radiansZ)))*(double)num),
		(float)((double)((float)cos((double)radiansZ))*(double)num),
		(float)sin((double)radiansX)
	};

	return ret_dir;
}

void Utils::WorkOutTimeSinceEntitySpawn(int age, int*hour, int*min, int*sec) {
	int ms = (GetGameTimer() - age) / 1000;
	*hour = ms / 3600;
	*min = (ms % 3600) / 60;
	*sec = ms % 60;
}

string Utils::SecondsToTime(int seconds) {
	int hour, min, second;
	hour = seconds / 3600;
	seconds %= 3600;
	min = seconds / 60;
	seconds %= 60;
	second = seconds;
	return pUtils.cprintf("%d hours, %d minutes and %d seconds", hour, min, second);
}

void Utils::RunFunctionAfterTime(int ms, function<void()> function) {
	TimedFunctions.push_back(SFunctionCallAfterTimer(GetGameTimer()/*gay bc cant call this from utils.h*/, ms, function));
}

void Utils::TimedFunctionManager() {
	for (int i = 0; i < TimedFunctions.size(); i++) {
		if (GetGameTimer() > TimedFunctions[i].timestamp) {
			TimedFunctions[i].function_();
			TimedFunctions.erase(TimedFunctions.begin() + i);
		}
	}
}

Raycast CastInfront(float length, Vector3 camCoord, int flag) {
	Vector3 infront;
	pUtils.GetCameraDirection(&infront.x, &infront.y, &infront.z);

	Vector3 target = Vector3(camCoord.x + (infront.x * length), camCoord.y + (infront.y * length), camCoord.z + (infront.z * length));

	return Raycast(SHAPETEST::_StartShapeTestRay(camCoord.x, camCoord.y, camCoord.z, target.x, target.y, target.z, flag, GetLocalPlayer().Ped, 0));
}

Raycast::Raycast(int handle): hitEntity(0) {
	Entity hitEn;
	SHAPETEST::GetShapeTestResult(handle, &hit, &endCoords, &surfaceNormal, &hitEn);
	if (DoesEntityExist(hit))
	{
		if (hitEntity != PlayerPedId() && GetEntityType(hitEn) == 1 || GetEntityType(hitEn) == 2 || GetEntityType(hitEn)
			== 3)
			hitEntity = hitEn;
		else
			hitEntity = NULL;
	}
	didHitEntity = hitEntity != NULL;
}

Vector3 GetAimingCoords() {
	Raycast raycast = CastInfront(25.0f, GetGameplayCamCoord(), -1);
	return raycast.endCoords;
}

