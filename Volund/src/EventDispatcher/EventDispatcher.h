#pragma once

#include "Event.h"

namespace Volund
{
	using EventHandler = void(*)(Volund::Event*);

	class EventDispatcher
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