#include "stdafx.h"

FiberManager pFiber;

void FiberManager::Init() {
	if (bInitialized) return;
	ConvertThreadToFiber(nullptr);
	pMainFiber = GetCurrentFiber();
	bInitialized = true;
}

void FiberManager::AddFiber(void(*function)()) {
	uint64_t* args = new uint64_t[2];
	args[0] = (uint64_t)function;
	args[1] = (uint64_t)pMainFiber;

	auto fiber = CreateFiber(NULL, [](void* pFiberParam) {
		uint64_t* arguments = (uint64_t*)pFiberParam;
		try {
			while (true) {
				((void(*)(void))arguments[0])();
				SwitchToFiber((void*)arguments[1]);
			}
		} catch (...) {
			delete[] arguments;
		}
	}, args);

	Fiber newFiber = { nullptr, fiber, timeGetTime() };
	ThreadFibers.push_back(newFiber);

	for (auto fiber = ThreadFibers.begin(); fiber != ThreadFibers.end(); ++fiber) {
		auto nextFiber = fiber + 1;
		if (nextFiber != ThreadFibers.end()) fiber->pNextFiber = &*nextFiber;
		else fiber->pNextFiber = &ThreadFibers.front();
	}

	pCurrentFiber = &ThreadFibers.front();
}

void FiberManager::Tick() {
	if (!pCurrentFiber || !bInitialized) return;

	for (Fiber& f : ThreadFibers) {
		if (timeGetTime() >= f.ulWaitTime) {
			SwitchToFiber(f.pFiber);
		}
	}

	pCurrentFiber = pCurrentFiber->pNextFiber;
}

void FiberManager::Sleep(unsigned long time) {
	auto fiber = find_if(ThreadFibers.begin(), ThreadFibers.end(), [](const Fiber& fiber) -> bool { return fiber.pFiber == GetCurrentFiber(); });
	if (fiber != ThreadFibers.end()) {
		fiber->ulWaitTime = timeGetTime() + time;
		SwitchToFiber(pMainFiber);
	}
}

void FiberManager::GoToMainFiber() {
	SwitchToFiber(pMainFiber);
}