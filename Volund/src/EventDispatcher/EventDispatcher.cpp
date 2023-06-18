#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		if ((e.Type & VOLUND_EVENT_TYPE_FLAG_ASYNC) != 0)
		{
			VOLUND_THREADPOOL_SUBMIT([this, e]() 
			{
				this->m_EventCallback(e);
			});
		}
		else
		{
			this->m_EventCallback(e);
		}
	}

	EventDispatcher::EventDispatcher(std::function<void(const Event&)> eventCallback)
	{
		this->m_EventCallback = eventCallback;
	}
}