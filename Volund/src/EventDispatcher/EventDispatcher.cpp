#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	EventDispatcher::EventDispatcher(Layer* L)
	{
		this->_Layer = L;
	}

	EventDispatcher::~EventDispatcher()
	{

	}

	void EventDispatcher::SendEventToLayer(Event* E)
	{
		this->_Layer->OnEvent(E);
	}
}