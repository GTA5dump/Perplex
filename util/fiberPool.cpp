#include "stdafx.h"

FiberPool pFiberPool;

void FiberPool::Init() {
	static function<void(void)> job1;
	static function<void(void)> job2;
	static function<void(void)> job3;
	static function<void(void)> job4;

	pFiber.AddFiber([] { pFiberPool.Update(job1); });
	pFiber.AddFiber([] { pFiberPool.Update(job2); });
	pFiber.AddFiber([] { pFiberPool.Update(job3); });
	pFiber.AddFiber([] { pFiberPool.Update(job4); });
}

void FiberPool::Update(function<void(void)>& func) {
	if (Jobs.empty()) return;
	func = std::move(Jobs.front());
	Jobs.pop();
	func();
}

void FiberPool::DoJob(function<void(void)> func) {
	Jobs.emplace(std::move(func));
}