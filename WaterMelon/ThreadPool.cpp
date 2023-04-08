#include "ThreadPool.hpp"

ThreadPool::ThreadPool(int ThreadCount)
{
	InitSize(ThreadCount);
}

ThreadPool::~ThreadPool()
{
	Destroy();
}

void ThreadPool::StartTask(ThreadPoolFunction Func)
{
	if (!m_running)
		ThrowException("Cant start a task when the ThreadPool is not up and running");

	int index = 0;
	while (true)
	{
		if (!m_threadsRunning[index])
		{
			m_functions[index] = Func;
			m_threadsRunning[index] = true;
			break;
		}

		index++;
		if (index == m_threadCount)
		{
			index = 0;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
}

void ThreadPool::InitSize(int ThreadCount)
{
	if (m_hasInit)
		return;

	ThrowNotImplementedException("Have not implemented Thread init array thingy");

	m_threadCount = ThreadCount;

	//m_threads = new std::thread[m_threadCount];
	//for (size_t i = 0; i < m_threadCount; i++)
		//m_threads[i].;

	//m_threads = (std::thread*)malloc(sizeof(std::thread) * m_threadCount);
	//ThreadPool* t = this;
	//for (int i = 0; i < m_threadCount; i++)
		//m_threads[i] = std::thread(&ThreadPool::ThreadRuntime, t, i);

	m_functions = new ThreadPoolFunction[m_threadCount]{ nullptr };
	m_threadsRunning = new bool[m_threadCount] {false};

	m_running = true;
}

void ThreadPool::Resize(int ThreadCount)
{
	Destroy();
	InitSize(ThreadCount);
}

void ThreadPool::Destroy()
{
	if (!m_hasInit)
		return;

	m_running = false;

	for (size_t i = 0; i < m_threadCount; i++)
	{
		m_threads[i].join();
		m_threads[i].~thread();
	}

	free(m_threads);
	delete[] m_functions;
	delete[] m_threadsRunning;

	m_hasInit = false;
}

int ThreadPool::ThreadCount()
{
	return m_threadCount;
}

bool ThreadPool::HasInit()
{
	return m_hasInit;
}

void ThreadPool::ThreadRuntime(ThreadPool& pool, int _id)
{
	while (true)
	{
		while (pool.m_functions[_id] == nullptr) // Waiting
		{
			std::cout << "H";
			if (!pool.m_running)
				return;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}


		ThreadPoolFunction func = pool.m_functions[_id];
		func();

		pool.m_functions[_id] = nullptr;
		pool.m_threadsRunning[_id] = false;
		if (!pool.m_running)
			return;
	}
}
