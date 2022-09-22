#pragma once

#include "Event.h"

namespace Volund
{
	class Application;

	class EventDispatcher
	{
	public:
		template <typename T>
		void Dispatch(T E);

		EventDispatcher(Application* App);

		~EventDispatcher();

	private:
		void SendEventToApp(Event* E) const;

		Application* _Application;
	};

	template <typename T>
	void EventDispatcher::Dispatch(T E)
	{
		this->SendEventToApp(static_cast<Event*>(&E));
	}
}
