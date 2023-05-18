#include "PCH/PCH.h"
#include "ThreadPool.h"

namespace Volund
{
	ThreadPool ThreadPool::m_GlobalPool = ThreadPool();

	void ThreadPool::Submit(ThreadJob job)
	{
#ifdef VOLUND_DISABLE_MULTITHREADING
		job();
#else
		{
			std::unique_lock lock(m_Mutex);
			this->m_JobQueue.push(job);
		}
		this->m_Condition.notify_one();
#endif
	}

	bool ThreadPool::Busy()
	{
		return !this->m_JobQueue.empty() || this->m_ActiveThreads != 0;
	}

	ThreadPool::ThreadPool()
	{
		this->m_ShouldTerminate = false;

		const uint64_t threadCount = std::thread::hardware_concurrency();
		this->m_Threads.resize(threadCount);
		for (uint64_t i = 0; i < threadCount; i++)
		{
			this->m_Threads[i] = std::thread([this]() { Loop(); });
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock lock(this->m_Mutex);
			this->m_ShouldTerminate = true;
		}

		this->m_Condition.notify_all();

		for (std::thread& activeThread : this->m_Threads)
		{
			activeThread.join();
		}
		this->m_Threads.clear();
	}

	ThreadPool& ThreadPool::GetGlobalPool()
	{
		return m_GlobalPool;
	}

	void ThreadPool::Loop()
	{		
		while (true)
		{
			ThreadJob job;
			{
				std::unique_lock lock(this->m_Mutex);
				this->m_Condition.wait(lock, [this]() { return this->m_ShouldTerminate || !this->m_JobQueue.empty(); });

				if (this->m_ShouldTerminate && this->m_JobQueue.empty())
				{
					return;
				}

				this->m_ActiveThreads++;

				job = this->m_JobQueue.front();
				this->m_JobQueue.pop();
			}

			job();

			this->m_ActiveThreads--;
		}
	}
}