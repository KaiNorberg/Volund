#include "PCH/PCH.h"
#include "ThreadPool.h"

namespace Volund
{
	void ThreadPool::Init()
	{
		if (ThreadPool::_IsInitialized)
		{
			return;
		}
		ThreadPool::_IsInitialized = true;
		ThreadPool::_ShouldTerminate = false;

		uint64_t ThreadCount = std::thread::hardware_concurrency();

		ThreadPool::_Threads.resize(ThreadCount);

		for (uint64_t i = 0; i < ThreadCount; i++)
		{
			ThreadPool::_Threads[i] = std::thread(ThreadPool::Loop);
		}
	}

	void ThreadPool::QueueJob(ThreadJob Job)
	{
		{
			std::unique_lock<std::mutex> lock(ThreadPool::_Mutex);
			ThreadPool::_Jobs.push(Job);
		}
		_MutexCondition.notify_one();
	}

	void ThreadPool::Terminate()
	{
		ThreadPool::_IsInitialized = false;
		{
			std::unique_lock<std::mutex> lock(ThreadPool::_Mutex);
			ThreadPool::_ShouldTerminate = true;
		}
		_MutexCondition.notify_all();

		for (std::thread& active_thread : ThreadPool::_Threads) 
		{
			active_thread.join();
		}
		ThreadPool::_Threads.clear();
	}

	bool ThreadPool::Busy()
	{
		bool Busy;
		{
			std::unique_lock<std::mutex> lock(ThreadPool::_Mutex);
			Busy = !ThreadPool::_Jobs.empty();
		}
		return Busy;
	}

	void ThreadPool::Loop()
	{
		while (true)
		{
			ThreadJob Job = nullptr;
			{
				std::unique_lock<std::mutex> lock(ThreadPool::_Mutex);

				_MutexCondition.wait(lock, [] 
				{
					return !ThreadPool::_Jobs.empty() || ThreadPool::_ShouldTerminate;
				});

				if (ThreadPool::_ShouldTerminate)
				{
					_MutexCondition.notify_all();
					return;
				}

				Job = ThreadPool::_Jobs.front();
				ThreadPool::_Jobs.pop();
			}
			Job();
		}
	}
}