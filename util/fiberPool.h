#pragma once

class FiberPool {
public:
	void Init();
	void Update(function<void(void)>& func);
	void DoJob(function<void(void)> func);

private:
	queue<function<void(void)>> Jobs;
};

extern FiberPool pFiberPool;