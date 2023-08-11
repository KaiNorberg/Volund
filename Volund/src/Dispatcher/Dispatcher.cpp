#include "PCH/PCH.h"

#include "Dispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void Dispatcher::Dispatch(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_EventQueue.push(e);
	}

	void Dispatcher::Dispatch(const Job& job)
	{
		VOLUND_PROFILE_FUNCTION();

		std::unique_lock lock(this->m_Mutex);

		this->m_JobQueue.push(job);
	}

	void Dispatcher::Execute()
	{
		while (!this->m_EventQueue.empty())
		{
			Event e = this->m_EventQueue.front();

			if ((e.Type & VOLUND_EVENT_TYPE_FLAG_ASYNC) != 0)
			{
				this->m_ThreadPool->Submit([this, e]() 
				{
					this->m_EventCallback(e);
				});
			}
			else
			{
				this->m_EventCallback(e);
			}

			this->m_EventQueue.pop();
		}

		while (!this->m_JobQueue.empty())
		{
			Job job = this->m_JobQueue.front();

			this->m_ThreadPool->Submit([this, job]()
			{
				std::unique_lock lock(this->m_Mutex);

				if (job.m_Task != nullptr)
				{
					job.m_Task();
				}

				if (job.m_CleanupTask != nullptr)
				{
					this->m_CleanupQueue.push(job.m_CleanupTask);
				}
			});

			this->m_JobQueue.pop();
		}

		while (!this->m_CleanupQueue.empty())
		{
			Task cleanupTask = this->m_CleanupQueue.front();

			cleanupTask();

			this->m_CleanupQueue.pop();
		}
	}

	Dispatcher::Dispatcher(std::function<void(const Event&)> eventCallback)
	{
		this->m_EventCallback = eventCallback;
		this->m_ThreadPool = std::make_shared<ThreadPool>();
	}
}