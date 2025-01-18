#include "ThreadPool.h"

namespace Volund
{
	bool ThreadPool::Busy()
	{
		return !this->m_taskQueue.empty() || this->m_activeWorkerCount != 0;
	}

	uint8_t ThreadPool::GetActiveWorkerCount()
	{
		return this->m_activeWorkerCount;
	}

	ThreadPool::ThreadPool(uint8_t threadCount)
	{
		for (uint64_t i = 0; i < threadCount; i++)
		{
			this->m_workers.push_back(std::thread([this]() { Loop(); }));
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			this->m_shouldTerminate = true;
		}

		m_condition.notify_all();

		for (std::thread& worker : this->m_workers) 
		{
			worker.join();
		}
		this->m_workers.clear();
	}

	void ThreadPool::Loop()
	{		
		while (true)
		{
			Task task;
			{
				std::unique_lock lock(this->m_mutex);

				this->m_condition.wait(lock, [this]() { return this->m_shouldTerminate || !this->m_taskQueue.empty(); });

				if (this->m_shouldTerminate && this->m_taskQueue.empty())
				{
					return;
				}

				this->m_activeWorkerCount++;

				task = std::move(this->m_taskQueue.front());
				this->m_taskQueue.pop();
			}

			task();

			this->m_activeWorkerCount--;
		}
	}
}