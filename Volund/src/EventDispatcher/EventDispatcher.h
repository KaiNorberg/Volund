#pragma once

#include "Event.h"

#pragma warning( push )
#pragma warning(disable : 4251)

namespace Volund
{
	using EventHandler = void(*)(Volund::Event*);

	class VOLUND_API EventDispatcher
	{
	public:

		void Dispatch();

		void PushEvent(Event* E);

		EventDispatcher();

	private:

		std::vector<Event*> _EventStack;

		std::unordered_map<EventType, EventHandler> _EventHandlers;
	};
}

#pragma warning( pop )