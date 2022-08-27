#pragma once

#include "EventDispatcher/Event.h"

#define KEY_AMOUNT 348
#define MOUSE_BUTTON_AMOUNT 8
 
#define MOUSE_BUTTON_MIDDLE 2
#define MOUSE_BUTTON_LEFT 0   
#define MOUSE_BUTTON_RIGHT 1   

#include "Math/Math.h"

namespace Volund
{
	class Application;

	void KeyHandler(Event* E, Application* App);
	void MouseButtonHandler(Event* E, Application* App);
	void ScrollHandler(Event* E, Application* App);
	void CursorPosHandler(Event* E, Application* App);

	class Input
	{
	public:

		static bool IsHeld(char KeyCode);
		static bool IsPressed(char KeyCode);

		static bool IsMouseButtonHeld(char Button);
		static bool IsMouseButtonPressed(char Button);

		static double GetScrollOffset();

		static Vec2 GetCursorPosition();

	private:
		
		friend void Volund::KeyHandler(Event* E, Application* App);
		friend void Volund::MouseButtonHandler(Event* E, Application* App);
		friend void Volund::ScrollHandler(Event* E, Application* App);
		friend void Volund::CursorPosHandler(Event* E, Application* App);

		static void SendKeyEvent(KeyEvent* KE);
		static void SendMouseButtonEvent(MouseButtonEvent* MBE);
		static void SendScrollEvent(ScrollEvent* SE);
		static void SendCursorPosEvent(CursorPosEvent* CPE);

		static Vec2 MousePosition;

		static double ScrollOffset;

		static int8_t MouseButtons[MOUSE_BUTTON_AMOUNT];
		static int8_t Keys[KEY_AMOUNT];
	};
}