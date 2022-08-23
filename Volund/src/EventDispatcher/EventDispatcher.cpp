#include "PCH/PCH.h"

#include "EventDispatcher.h"
#include "Input/Input.h"

namespace Volund
{
	void WindowCloseHandler(Event* E)
	{
		WindowCloseEvent* WCE = (WindowCloseEvent*)E;

		exit(EXIT_SUCCESS);
	}

	void WindowSizeHandler(Event* E)
	{
		WindowSizeEvent* WSE = (WindowSizeEvent*)E;

		//TODO
	}

	void KeyHandler(Event* E)
	{
		KeyEvent* KE = (KeyEvent*)E;

		Input::SendKeyEvent(KE);

		//TODO
	}

	void MouseButtonHandler(Event* E)
	{
		MouseButtonEvent* MBE = (MouseButtonEvent*)E;

		Input::SendMouseButtonEvent(MBE);

		//TODO
	}

	void ScrollHandler(Event* E)
	{
		ScrollEvent* SE = (ScrollEvent*)E;

		//TODO
	}

	void CursorPosHandler(Event* E)
	{
		CursorPosEvent* CPE = (CursorPosEvent*)E;

		//TODO
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void EventDispatcher::Dispatch()
	{
		while (this->_EventStack.size() != 0)
		{
			Event* E = this->_EventStack.back();

			this->_EventHandlers[E->GetType()](E);

			this->_EventStack.pop_back();
			delete E;
		}
	}

	void EventDispatcher::PushEvent(Event* E)
	{	
		this->_EventStack.push_back(E);
	}

	EventDispatcher::EventDispatcher()
	{
		this->_EventStack.reserve(16); 
		
		_EventHandlers =
		{
			{EventType::NONE, nullptr},
			{EventType::WINDOW_CLOSE, WindowCloseHandler},
			{EventType::WINDOW_SIZE, WindowSizeHandler},
			{EventType::KEY, KeyHandler},
			{EventType::MOUSE_BUTTON, MouseButtonHandler},
			{EventType::SCROLL, ScrollHandler},
			{EventType::CURSOR_POS, CursorPosHandler}
		};
	}
}