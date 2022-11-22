#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	EventDispatcher::EventDispatcher(Application* App)
	{
		this->_Application = App;
	}

	EventDispatcher::~EventDispatcher()
	{

	}

	void EventDispatcher::SendEventToApp(Event* E) const
	{
		this->_Application->EventCallback(E);
	}
}