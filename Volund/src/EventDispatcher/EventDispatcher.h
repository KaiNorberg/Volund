#pragma once

#include "Event.h"

#include "Input/Input.h"

namespace Volund
{
	class Application;

	class EventDispatcher
	{
	public:

		template<typename T>
		void Dispatch(T E);

		EventDispatcher(Application* App);

		~EventDispatcher();

	private:

		template<typename T>
		void EventHandler(T E);

		void SendEventToApp(Event* E);

		Application* _Application;
	};

	template<typename T>
	void EventDispatcher::Dispatch(T E)
	{
		EventHandler(E);

		this->SendEventToApp(static_cast<Event*>(&E));
	}
}