#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

namespace Volund
{
	EventDispatcher::EventDispatcher(EventCallback Callback)
	{
		this->_Callback = Callback;
	}

	EventDispatcher::~EventDispatcher()
	{

	}
}