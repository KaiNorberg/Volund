#pragma once

#include "Event.h"

namespace Volund
{
	using EventCallback = void(*)(Event*);

	class EventDispatcher
	{
	public:

		template<typename T>
		void Dispatch(T E);

		EventDispatcher(EventCallback CallBack);

		~EventDispatcher();

	private:

		template<typename T>
		void Handler(T E);

		EventCallback _Callback;
	};

	template<typename T>
	void EventDispatcher::Dispatch(T E)
	{
		Handler(E);

		if (this->_Callback != nullptr)
		{
			this->_Callback(static_cast<Event*>(&E));
		}
	}

	template<>
	void EventDispatcher::Handler<WindowCloseEvent>(WindowCloseEvent E)
	{

	}

	template<>
	void EventDispatcher::Handler<WindowSizeEvent>(WindowSizeEvent E)
	{
		//TODO
	}

	template<>
	void EventDispatcher::Handler<KeyEvent>(KeyEvent E)
	{
		Input::SendKeyEvent(E);

		//TODO
	}

	template<>
	void EventDispatcher::Handler<MouseButtonEvent>(MouseButtonEvent E)
	{
		Input::SendMouseButtonEvent(E);

		//TODO
	}

	template<>
	void EventDispatcher::Handler<ScrollEvent>(ScrollEvent E)
	{
		Input::SendScrollEvent(E);

		//TODO
	}

	template<>
	void EventDispatcher::Handler<CursorPosEvent>(CursorPosEvent E)
	{
		Input::SendCursorPosEvent(E);

		//TODO
	}
}