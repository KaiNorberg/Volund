#include "PCH/PCH.h"
#include "ThreadPool.h"

namespace Volund
{
	ThreadPool ThreadPool::_GlobalPool = ThreadPool();

	void ThreadPool::Submit(ThreadJob Job)
	{
		{
			std::unique_lock Lock(_Mutex);
			this->_JobQueue.push(Job);
		}
		this->_Condition.notify_one();
	}

	bool ThreadPool::Busy()
	{
		return !this->_JobQueue.empty() || this->_ActiveThreads != 0;
	}

	ThreadPool::ThreadPool()
	{
		this->_ShouldTerminate = false;

		uint64_t ThreadCount = std::thread::hardware_concurrency();
		this->_Threads.resize(ThreadCount);
		for (uint64_t i = 0; i < ThreadCount; i++)
		{
			this->_Threads[i] = std::thread([this]() { Loop(); });
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock Lock(this->_Mutex);
			this->_ShouldTerminate = true;
		}

		this->_Condition.notify_all();

		for (std::thread& active_thread : this->_Threads)
		{
			active_thread.join();
		}
		this->_Threads.clear();
	}

	ThreadPool& ThreadPool::GetGlobalPool()
	{
		return _GlobalPool;
	}

	void ThreadPool::Loop()
	{		
		while (true)
		{
			ThreadJob Job;
			{
				std::unique_lock Lock(this->_Mutex);
				this->_Condition.wait(Lock, [this]() { return this->_ShouldTerminate || !this->_JobQueue.empty(); });

				if (this->_ShouldTerminate && this->_JobQueue.empty())
				{
					return;
				}

				this->_ActiveThreads++;

				Job = this->_JobQueue.front();
				this->_JobQueue.pop();
			}

			Job();

			this->_ActiveThreads--;
		}
	}
}