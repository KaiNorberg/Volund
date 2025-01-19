#include "Dispatcher.h"
#include "Input.h"

#include "Application.h"

namespace Volund
{
	void Dispatcher::Enqueue(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_eventQueue.push(e);
	}

	void Dispatcher::Enqueue(const Job& job)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_jobQueue.push(job);
	}

	void Dispatcher::Enqueue(const Task& deferredTask)
	{
		this->m_deferredQueue.push(deferredTask);
	}

	void Dispatcher::Dispatch()
	{
		if (this->m_jobQueue.empty() && this->m_cleanupQueue.empty() && this->m_threadPool->GetActiveWorkerCount() == 0)
		{
			while (!this->m_deferredQueue.empty())
			{
				Task deferredTask = this->m_deferredQueue.front();
				this->m_deferredQueue.pop();

				deferredTask();
			}
		}

		while (!this->m_eventQueue.empty())
		{
			Event e = this->m_eventQueue.front();
			this->m_eventQueue.pop();

			if ((e.type & VOLUND_EVENT_FLAG_ASYNC) != 0)
			{
				this->m_threadPool->Submit([this, e]()
				{
					this->m_eventCallback(e);
				});
			}
			else
			{
				this->m_eventCallback(e);
			}
		}

		while (!this->m_jobQueue.empty())
		{
			Job job = this->m_jobQueue.front();
			this->m_jobQueue.pop();

			this->m_threadPool->Submit([this, job]()
			{
				if (job.m_task != nullptr)
				{
					job.m_task();
				}

				if (job.m_cleanupTask != nullptr)
				{
					std::unique_lock lock(this->m_mutex);

					this->m_cleanupQueue.push(job.m_cleanupTask);
				}
			});
		}

		std::unique_lock lock(this->m_mutex);

		while (!this->m_cleanupQueue.empty())
		{
			Task cleanupTask = this->m_cleanupQueue.front();
			this->m_cleanupQueue.pop();

			cleanupTask();
		}
	}

	Dispatcher::Dispatcher(std::function<void(const Event&)> eventCallback)
	{
		this->m_eventCallback = eventCallback;
		this->m_threadPool = std::make_shared<ThreadPool>(8);
	}

	Dispatcher::~Dispatcher()
	{
		this->Dispatch();
	}
}
