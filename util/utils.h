#pragma once
#include "config.h"

extern unordered_map<AuthSignatures, uint64_t> ResolvedSignatures;

struct RadioData {
	bool bToggle[100];
	int iSelected;
	int iCount;
};

struct ImageSection {
	uint64_t dwPointer;
	uint64_t dwSize;
};

struct SFunctionCallAfterTimer {
	int timestamp;
	function<void()> function_;

	SFunctionCallAfterTimer(int a, int b, function<void()> c) {
		timestamp = a + b; function_ = c;
	}
};

struct HandleData {
	DWORD pid;
	HWND hWnd;
};

class Utils {
public:
	void CloseProc(string error = NULL);
	void DisplayMessageBox(const char* messagebox);
	ImageSection GetTextSection(HMODULE hModule, vector<char> originalPE);
	bool IsProcessRunning(const char* processName);

	vector<string> Split(const char *str, char c = ' ');
	vector<string> ResolveFileNamesFromFolder(string folder, string extension, int removeFromEndChars = 0);
	string GenerateRandomString(int length);
	const char* cprintf(const char* format, ...);
	void VABuffer(char* buffer, int bufferSize, const char* format, ...);
	void RunTimedFunction(int* timer, int ms, function<void()> function);
	void GetCameraDirection(float *dirX, float *dirY, float *dirZ, Vector3 rotation = Vector3());
	Vector3 RotateToDirection(Vector3*rot);
	void WorkOutTimeSinceEntitySpawn(int age, int*hour, int*min, int*sec);
	string SecondsToTime(int seconds);
	wchar_t *CharToWCHART(const char* charArray);

	vector<SFunctionCallAfterTimer>TimedFunctions;
	void RunFunctionAfterTime(int ms, function<void()> function);
	void TimedFunctionManager();

	bool IsValidJSONResponse(string json);
	bool DoesStingHaveInvalidChars(string input);

	string IntToString(int value) {
		return cprintf("%d", value);
	}

	HWND FindMainWindow(DWORD dwPID);

	QAngle CalcAngle(const Vector& src, const Vector& dst) {
		QAngle srca = { src.x, src.y, src.z };
		QAngle dsta = { dst.x, dst.y, dst.z };

		QAngle angle;
		QAngle delta = srca - dsta;

		double hyp = sqrtf((double)(delta.x * delta.x) + (delta.y * delta.y));
		angle.x = atan(delta.z / hyp) * 57.295779513082f;
		angle.y = atan(delta.y / delta.x) * 57.295779513082f;
		if (delta.x >= 0.0) angle.y += 180.0f;


		return angle;
	}

	template <class Type>
	void TransaitionFloatToValue(float& fl0at, Type value, float increment = 0.01f) {
		if (fl0at != (float)value) {
			if (fl0at > (float)value) {
				if ((fl0at - increment) < (float)value)
					fl0at = (float)value;
				else
					fl0at -= increment;

			} else if (fl0at < (float)value) {
				if ((fl0at + increment) > (float)value)
					fl0at = (float)value;
				else
					fl0at += increment;
			}
		}
	}

	template<typename T>
	bool Within(T val, T min, T max) {
		return val <= max && val >= min;
	}

	int Clamp(int val, int min, int max) {
		return val < min ? min : val > max ? max : val;
	}

	float Clamp(float val, float min, float max) {
		return val < min ? min : val > max ? max : val;
	}

	void Clamp(int *val, int min, int max) {
		*val = *val < min ? min : *val > max ? max : *val;
	}

	bool Clamp(float *val, float min, float max) {
		*val = *val < min ? min : *val > max ? max : *val;
		return *val == min || *val == max;
	}

	float GetDistanceBetweenCoords(Vector3 start, Vector3 end) {
		return ((float)sqrt(pow(end.x - start.x, 2) +
			pow(end.y - start.y, 2) * 1.0));
	}

	float DegToRad(float degs) {
		return degs * 3.141592653589793f / 180.f;
	}

	Vector3 get_coords_infront_of_coords(Vector3 pos, Vector3 rot, float dist) {
		Vector3 ret;

		float a = pos.x + (RotateToDirection(&rot).x * dist);
		float b = pos.y + (RotateToDirection(&rot).y * dist);
		float c = pos.z + (RotateToDirection(&rot).z * dist);

		ret.x = a;
		ret.y = b;
		ret.z = c;

		return ret;
	}

	float Get3dDistance(Vector3 mycoords, Vector3 targetcoords) {
		return sqrt(pow(double(targetcoords.x - mycoords.x), 2.0f) +
					pow(double(targetcoords.y - mycoords.y), 2.0f) +
					pow(double(targetcoords.z - mycoords.z), 2.0f)
		);
	}

	SimpleVector2 CalculateAngle(Vector3 src, Vector3 dst) {
		SimpleVector2 out;
		double delta[3] = { (src.x - dst.x), (src.y - dst.y), (src.z - dst.z) };
		double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
		out.x = (float)(asinf(delta[2] / hyp) * 57.295779513082f);
		out.y = (float)(asinf(delta[1] / delta[0]) * 57.295779513082f);
		//angle[2] = 0.0f;

		if (delta[0] >= 0.0) {
			out.y += 180.0f;
		}

		return out;
	}
};

extern Utils pUtils;

static void LOG_PUBLIC(const char* formatter, ...) {
	char buffer[0x500];
	char datebuffer[30];
	va_list ap;
	va_start(ap, formatter);
	vsprintf_s(buffer, formatter, ap);
	va_end(ap);

	OutputDebugStringA(pUtils.cprintf("[Perplex] %s\n"_Protect, buffer));

	ofstream output(pUtils.cprintf("%s/log.txt"_Protect, pConfig.GetPerplexGTARootPath().c_str()), ios_base::app);
	if (output.good()) {
		auto stamp = time(nullptr);
		auto datetime = localtime(&stamp);
		strftime(datebuffer, sizeof(buffer), "%H:%M:%S"_Protect, datetime);
		output << pUtils.cprintf("[%s] %s"_Protect, datebuffer, buffer) << endl;
	}

	LOG_DEV("%s", buffer);

	ZeroMemory(buffer, 0x500);
	ZeroMemory(datebuffer, 30);
	output.close();
}

class Raycast {
public:
	Entity hitEntity;
	bool hit;
	Vector3 endCoords;
	Vector3 surfaceNormal;
	bool didHitEntity;

	Raycast(int handle);
};

Raycast CastInfront(float length, Vector3 camCoord, int flag);
Vector3 GetAimingCoords();
