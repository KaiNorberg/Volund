#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

#include "Application/Application.h"

namespace Volund
{
	void WindowCloseHandler(Event* E, Application* App)
	{
		WindowCloseEvent* WCE = (WindowCloseEvent*)E;

		App->Terminate();
	}

	void WindowSizeHandler(Event* E, Application* App)
	{
		WindowSizeEvent* WSE = (WindowSizeEvent*)E;

		//TODO
	}

	void KeyHandler(Event* E, Application* App)
	{
		KeyEvent* KE = (KeyEvent*)E;

		Input::SendKeyEvent(KE);

		//TODO
	}

	void MouseButtonHandler(Event* E, Application* App)
	{
		MouseButtonEvent* MBE = (MouseButtonEvent*)E;

		Input::SendMouseButtonEvent(MBE);

		//TODO
	}

	void ScrollHandler(Event* E, Application* App)
	{
		ScrollEvent* SE = (ScrollEvent*)E;

		Input::SendScrollEvent(SE);

		//TODO
	}

	void CursorPosHandler(Event* E, Application* App)
	{
		CursorPosEvent* CPE = (CursorPosEvent*)E;

		Input::SendCursorPosEvent(CPE);

		//TODO
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::unordered_map<EventType, EventHandler> EventDispatcher::_EventHandlers = 
	{
		{EventType::NONE, nullptr},
		{EventType::WINDOW_CLOSE, WindowCloseHandler},
		{EventType::WINDOW_SIZE, WindowSizeHandler},
		{EventType::KEY, KeyHandler},
		{EventType::MOUSE_BUTTON, MouseButtonHandler},
		{EventType::SCROLL, ScrollHandler},
		{EventType::CURSOR_POS, CursorPosHandler}
	};

	void EventDispatcher::Dispatch(Event* E)
	{
		this->_EventHandlers[E->GetType()](E, this->_Application);

		delete E;
	}

	EventDispatcher::EventDispatcher(Application* App)
	{
		this->_Application = App;
	}

	EventDispatcher::~EventDispatcher()
	{

	}
}