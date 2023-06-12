#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_EventCallback(e);
	}

	EventDispatcher::EventDispatcher(std::function<void(const Event&)> eventCallback)
	{
		this->m_EventCallback = eventCallback;
	}
}