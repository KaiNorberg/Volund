#include "PCH/PCH.h"
#include "ThreadPool.h"

namespace Volund
{
	void ThreadPool::Submit(ThreadJob Job)
	{
		{
			std::unique_lock Lock(_Mutex);
			_JobQueue.push(Job);
		}
		_Condition.notify_one();
	}

	bool ThreadPool::Busy()
	{
		return !_JobQueue.empty() || _ActiveThreads != 0;
	}

	ThreadPool::ThreadPool()
	{
		ThreadPool::_ShouldTerminate = false;

		uint64_t ThreadCount = std::thread::hardware_concurrency();
		_Threads.resize(ThreadCount);
		for (uint64_t i = 0; i < ThreadCount; i++)
		{
			_Threads[i] = std::thread([this]() { Loop(); });
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock Lock(_Mutex);
			_ShouldTerminate = true;
		}

		_Condition.notify_all();

		for (std::thread& active_thread : _Threads)
		{
			active_thread.join();
		}
		_Threads.clear();
	}


	void ThreadPool::Loop()
	{		
		while (true)
		{
			ThreadJob Job;
			{
				std::unique_lock Lock(_Mutex);
				_Condition.wait(Lock, [this]() { return _ShouldTerminate || !_JobQueue.empty(); });

				if (_ShouldTerminate && _JobQueue.empty())
				{
					return;
				}

				_ActiveThreads++;

				Job = _JobQueue.front();
				_JobQueue.pop();
			}

			Job();

			_ActiveThreads--;
		}
	}
}