#include "PCH/PCH.h"
#include "ThreadPool.h"

namespace Volund
{
	bool ThreadPool::Busy()
	{
		return !this->m_TaskQueue.empty() || this->m_ActiveWorkers != 0;
	}

	ThreadPool::ThreadPool(uint8_t threadCount)
	{
		for (uint64_t i = 0; i < threadCount; i++)
		{
			this->m_Workers.push_back(std::thread([this]() { Loop(); }));
		}
	}

	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			this->m_ShouldTerminate = true;
		}

		m_Condition.notify_all();

		for (std::thread& worker : this->m_Workers) 
		{
			worker.join();
		}
		this->m_Workers.clear();
	}

	void ThreadPool::Loop()
	{		
		while (true)
		{
			Task task;
			{
				std::unique_lock lock(this->m_Mutex);

				this->m_ActiveWorkers--;

				this->m_Condition.wait(lock, [this]() { return this->m_ShouldTerminate || !this->m_TaskQueue.empty(); });

				if (this->m_ShouldTerminate && this->m_TaskQueue.empty())
				{
					return;
				}

				this->m_ActiveWorkers++;

				task = std::move(this->m_TaskQueue.front());
				this->m_TaskQueue.pop();
			}

			task();
		}
	}
}