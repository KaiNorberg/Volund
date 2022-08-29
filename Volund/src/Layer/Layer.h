#pragma once

#include "Time/Time.h"

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Layer
	{
	public:

		virtual void OnAttach() {};

		virtual void OnDetach() {};

		virtual void OnUpdate(TimeStep TS) {};
	
		virtual void OnEvent(Event* E) {};

		virtual ~Layer() {}
	};
}