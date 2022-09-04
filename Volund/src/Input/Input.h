#pragma once

#include "EventDispatcher/Event.h"

#define VOLUND_KEY_AMOUNT 348
#define VOLUND_MOUSE_BUTTON_AMOUNT 8
 
#define VOLUND_MOUSE_BUTTON_MIDDLE 2
#define VOLUND_MOUSE_BUTTON_LEFT 0   
#define VOLUND_MOUSE_BUTTON_RIGHT 1   

namespace Volund
{
	class Application;

	class Input
	{
	public:

		static bool IsHeld(char KeyCode);
		static bool IsPressed(char KeyCode);

		static bool IsMouseButtonHeld(char Button);
		static bool IsMouseButtonPressed(char Button);

		static double GetScrollOffset();

		static DVec2 GetCursorPosition();

		static void SendEvent(KeyEvent E);
		static void SendEvent(MouseButtonEvent E);
		static void SendEvent(ScrollEvent E);
		static void SendEvent(CursorPosEvent E);

	private:

		static DVec2 CursorPosition;

		static double ScrollOffset;

		static int8_t MouseButtons[VOLUND_MOUSE_BUTTON_AMOUNT];
		static int8_t Keys[VOLUND_KEY_AMOUNT];
	};
}