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

	void EventDispatcher::SendEventToApp(Event* E)
	{
		this->_Application->EventCallback(E);
	}

	template<>
	void EventDispatcher::EventHandler(WindowCloseEvent E)
	{

	}

	template<>
	void EventDispatcher::EventHandler(WindowSizeEvent E)
	{

	}

	template<>
	void EventDispatcher::EventHandler(KeyEvent E)
	{
		Input::SendEvent(E);
	}

	template<>
	void EventDispatcher::EventHandler(MouseButtonEvent E)
	{
		Input::SendEvent(E);
	}

	template<>
	void EventDispatcher::EventHandler(ScrollEvent E)
	{
		Input::SendEvent(E);
	}

	template<>
	void EventDispatcher::EventHandler(CursorPosEvent E)
	{
		Input::SendEvent(E);
	}
}