#pragma once

class Thread {
private:
	const char* pName;
	HANDLE hThread;
	bool bIsRunning;

public:
	Thread() : pName(""), hThread(0), bIsRunning(true) {}
	Thread(const char* name) : pName(name), hThread(0), bIsRunning(true) {}

	void SetHandle(HANDLE handle) { hThread = handle; }
	HANDLE GetHandle() { return hThread; }

	void Shutdown() { bIsRunning = false; }
	void Destroy() { TerminateThread(hThread, 0); }
	bool IsRunning() { return bIsRunning; }
	const char* GetName() { return pName; }
};

class ThreadPool {
public:

	void Initialize(int threads);
	void Cleanup();
	void Remove(const char* name, bool destroy = false);
	void DoJob(function<void(void)> func);
	bool IsInitialized() { return bInitialized; }
	Thread* RegisterThread(const char* name, void(*func)());
	vector<Thread*> GetThreads() { return Threads; }
private:
	vector<Thread*> Threads;
	vector<thread> JobThreads;
	bool bShutdown = false;
	bool bInitialized = false;
	mutex MutexLock;
	condition_variable Condition;
	queue<function<void(void)>> Jobs;
	void ThreadEntry(int index);
};

extern ThreadPool pThreadPool;