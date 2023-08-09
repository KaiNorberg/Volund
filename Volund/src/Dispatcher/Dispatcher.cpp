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

		this->m_ThreadPool->Submit([this, job]() 
		{			
			std::unique_lock lock(this->m_Mutex);

			job.m_Task();
			this->m_CleanupQueue.push(job.m_CleanupTask);
		});
	}

	void Dispatcher::Execute()
	{
		while (!this->m_EventQueue.empty())
		{
			Event e = this->m_EventQueue.front();

			if ((e.Type & VOLUND_EVENT_TYPE_FLAG_ASYNC) != 0)
			{
				this->Dispatch(Job([this, e]()
				{
					this->m_EventCallback(e);
				}, nullptr));
			}
			else
			{
				this->m_EventCallback(e);
			}

			this->m_EventQueue.pop();
		}

		while (!this->m_CleanupQueue.empty())
		{
			Task cleanupTask = this->m_CleanupQueue.front();
		
			if (cleanupTask != nullptr)
			{
				cleanupTask();
			}

			this->m_CleanupQueue.pop();
		}
	}

	Dispatcher::Dispatcher(std::function<void(const Event&)> eventCallback)
	{
		this->m_EventCallback = eventCallback;
		this->m_ThreadPool = std::make_shared<ThreadPool>();
	}
}