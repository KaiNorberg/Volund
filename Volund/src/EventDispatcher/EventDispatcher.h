#pragma once

#include "Event.h"

namespace Volund
{
	class Application;

	using EventHandler = void(*)(Volund::Event*, Volund::Application*);

	class EventDispatcher
	{
	public:

		void Dispatch(Event* E);

		EventDispatcher(Application* App);

		~EventDispatcher();

	private:

		Application* _Application;

		static std::unordered_map<EventType, EventHandler> _EventHandlers;
	};
}