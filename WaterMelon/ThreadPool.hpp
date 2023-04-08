#pragma once

#include <thread>
#include <chrono>
#include <iostream>

#include "ThrowHelper.hpp"

typedef void(*ThreadPoolFunction)();

/// <summary>
/// Used for easy multi threading.
/// Later have each thread have their own UnsafeWatermelon, and instead of copying everytime we just make the same moves as the real game
/// </summary>
class ThreadPool
{
public:
	ThreadPool(int ThreadCount);
	~ThreadPool();

	void StartTask(ThreadPoolFunction Func);

	void InitSize(int ThreadCount);
	void Resize(int ThreadCount);
	void Destroy();

	int ThreadCount();
	bool HasInit();
private:
	bool m_hasInit = false;
	int m_threadCount;

	std::thread* m_threads;
	ThreadPoolFunction* m_functions;
	bool* m_threadsRunning;
	bool m_running = false;

	static void ThreadRuntime(ThreadPool& pool, int _id);
};