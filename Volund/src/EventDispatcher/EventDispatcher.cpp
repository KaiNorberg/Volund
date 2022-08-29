#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	EventDispatcher::EventDispatcher(Application* App)
	{
		this->_Application = App;
	}

	EventDispatcher::~EventDispatcher()
	{

	}

	void EventDispatcher::OnEvent(Event* E)
	{
		this->_Application->OnEvent(E);
	}

	template<>
	void EventDispatcher::Handler(WindowCloseEvent E)
	{

	}

	template<>
	void EventDispatcher::Handler(WindowSizeEvent E)
	{
		//TODO
	}

	template<>
	void EventDispatcher::Handler(KeyEvent E)
	{
		Input::SendEvent(E);

		//TODO
	}

	template<>
	void EventDispatcher::Handler(MouseButtonEvent E)
	{
		Input::SendEvent(E);

		//TODO
	}

	template<>
	void EventDispatcher::Handler(ScrollEvent E)
	{
		Input::SendEvent(E);

		//TODO
	}

	template<>
	void EventDispatcher::Handler(CursorPosEvent E)
	{
		Input::SendEvent(E);

		//TODO
	}
}