#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void EventDispatcher::Dispatch(Event* E)
	{
		this->_App->EventCallback(E);
	}

	EventDispatcher::EventDispatcher(Application* App)
	{
		this->_App = App;
	}
}