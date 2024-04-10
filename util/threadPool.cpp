#include "stdafx.h"

ThreadPool pThreadPool;

void ThreadPool::Initialize(int threads) {
	if (bInitialized) return;
	bInitialized = true;
	JobThreads.reserve(threads);

	for (int i = 0; i < threads; ++i)
		JobThreads.emplace_back(bind(&ThreadPool::ThreadEntry, this, i));
}

void ThreadPool::Cleanup() {
	unique_lock<mutex> l(MutexLock);

	bShutdown = true;
	Condition.notify_all();

	for (auto& c_thread : Threads) {
		c_thread->Shutdown();
	}

	for (auto& c_thread : JobThreads) {
		c_thread.join();
	}
}

void ThreadPool::DoJob(std::function <void(void)> func) {
	if (!bInitialized) {
		return;
	}

	unique_lock<mutex> l(MutexLock);
	Jobs.emplace(std::move(func));
	Condition.notify_one();
}

void ThreadPool::ThreadEntry(int index) {
	function <void(void)> job;
	while (1) {
		unique_lock<mutex> lock(MutexLock);
		while (!bShutdown && Jobs.empty()) Condition.wait(lock);
		if (Jobs.empty())return;
		job = move(Jobs.front());
		Jobs.pop();
		job();
	}
}

void ThreadPool::Remove(const char* name, bool destroy) {
	/*auto vit = find(m_threads.begin(), m_threads.end(), name);
	if (vit != m_threads.end()) {
		auto item = (*vit);
		if (destroy) {
			item->destroy();
		}

		item->shutdown();
	}*/
}

Thread* ThreadPool::RegisterThread(const char* name, void(*func)()) {
	Thread* c_thread = new Thread(name);
	UINT64* args = new UINT64[3]{ 0, (UINT64)c_thread, (UINT64)func };

	c_thread->SetHandle(CreateThread(0, 0, [](LPVOID lpFiberParameter) -> DWORD {
		UINT64* arguments = (UINT64*)lpFiberParameter;
		try {
			while ((*(Thread*)arguments[1]).IsRunning()) {
				((void(*)(void)) arguments[2])();
			}
		} catch (...) {
			delete[] arguments;
		}
		return 1;
	}, args, 0, 0));

	typedef NTSTATUS(NTAPI* pNtSetInformationThread)(HANDLE thread, UINT type, PVOID unk1, DWORD unk2);
	const auto NtSetInformationThread = reinterpret_cast<pNtSetInformationThread>(GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtSetInformationThread"));

	if (NtSetInformationThread) {
		NtSetInformationThread(c_thread->GetHandle(), 17, 0, 0);
	}

	Threads.push_back(c_thread);
	return c_thread;
}