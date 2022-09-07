#pragma once

#include "EventDispatcher/Event.h"

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

		static uint32_t GetScrollPosition();

		static IVec2 GetMousePosition();

		static void SendEvent(KeyEvent E);
		static void SendEvent(MouseButtonEvent E);
		static void SendEvent(ScrollEvent E);
		static void SendEvent(MouseMoveEvent E);

	private:

		static inline IVec2 MousePosition;

		static inline uint32_t ScrollPosition;

		static inline int8_t MouseButtons[VOLUND_MOUSE_BUTTON_AMOUNT];
		static inline int8_t Keys[VOLUND_KEY_AMOUNT];
	};
}