#include "PCH/PCH.h"
#include "ThreadPool.h"

namespace Volund
{
	void ThreadPool::Init()
	{
		static bool Initialized = false;

		if (Initialized)
		{
			return;
		}

		Initialized = true;

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

	void ThreadPool::Wait()
	{
		for (auto& Thread : ThreadPool::_Threads)
		{
			Thread.join();
		} 
		
		ThreadPool::_Threads.clear();
	}

	bool ThreadPool::ShouldTerminate()
	{
		return ThreadPool::_ActiveJobCount == 0 && ThreadPool::_Jobs.empty();
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
					return !ThreadPool::_Jobs.empty() || ThreadPool::ShouldTerminate();
				});

				if (ThreadPool::ShouldTerminate())
				{
					_MutexCondition.notify_all();
					return;
				}

				Job = ThreadPool::_Jobs.front();
				ThreadPool::_Jobs.pop();
			}

			ThreadPool::_ActiveJobCount++;
			Job();
			ThreadPool::_ActiveJobCount--;
		}
	}
}