#pragma once

#include "EventDispatcher/Event.h"

#define KEY_AMOUNT GLFW_KEY_LAST
#define MOUSE_BUTTON_AMOUNT GLFW_MOUSE_BUTTON_LAST
 
#define MOUSE_BUTTON_MIDDLE GLFW_MOUSE_BUTTON_MIDDLE
#define MOUSE_BUTTON_LEFT GLFW_MOUSE_BUTTON_LEFT   
#define MOUSE_BUTTON_RIGHT GLFW_MOUSE_BUTTON_RIGHT   

namespace Volund
{
	void KeyHandler(Event* E);
	void MouseButtonHandler(Event* E);

	class Input
	{
	public:

		static bool IsHeld(char KeyCode);
		static bool IsPressed(char KeyCode);

		static bool IsMouseButtonHeld(char Button);
		static bool IsMouseButtonPressed(char Button);

	private:
		
		friend void Volund::KeyHandler(Event* E);
		friend void Volund::MouseButtonHandler(Event* E);

		static void SendKeyEvent(KeyEvent* KE);
		static void SendMouseButtonEvent(MouseButtonEvent* MBE);

		static int8_t MouseButtons[MOUSE_BUTTON_AMOUNT];
		static int8_t Keys[KEY_AMOUNT];
	};
}