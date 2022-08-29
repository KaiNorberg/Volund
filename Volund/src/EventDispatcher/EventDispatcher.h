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
		void Handler(T E);

		void OnEvent(Event* E);

		Application* _Application;
	};

	template<typename T>
	void EventDispatcher::Dispatch(T E)
	{
		Handler(E);

		this->OnEvent(static_cast<Event*>(&E));
	}
}