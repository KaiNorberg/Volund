#pragma once

#include "EventDispatcher/Event.h"

#define KEY_AMOUNT 348
#define MOUSE_BUTTON_AMOUNT 8
 
#define MOUSE_BUTTON_MIDDLE 2
#define MOUSE_BUTTON_LEFT 0   
#define MOUSE_BUTTON_RIGHT 1   

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

		static Vec2 GetCursorPosition();

		static void SendEvent(KeyEvent E);
		static void SendEvent(MouseButtonEvent E);
		static void SendEvent(ScrollEvent E);
		static void SendEvent(CursorPosEvent E);

	private:

		static Vec2 MousePosition;

		static double ScrollOffset;

		static int8_t MouseButtons[MOUSE_BUTTON_AMOUNT];
		static int8_t Keys[KEY_AMOUNT];
	};
}