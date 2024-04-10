#pragma once

struct Fiber {
	Fiber* pNextFiber;
	void* pFiber;
	unsigned long ulWaitTime;
};

class FiberManager {
public:
	void Init();
	void Tick();
	void AddFiber(void(*function)());
	void Sleep(unsigned long time);
	void GoToMainFiber();
	
private:
	vector<Fiber> ThreadFibers;
	void* pMainFiber;
	Fiber* pCurrentFiber;
	bool bInitialized;
};

extern FiberManager pFiber;

void WAIT(unsigned long time);