#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Input
	{
	public:
		bool IsHeld(char KeyCode) const;
		bool IsPressed(char KeyCode);

		bool IsMouseButtonHeld(char Button) const;
		bool IsMouseButtonPressed(char Button);

		uint32_t GetScrollPosition() const;

		IVec2 GetMousePosition() const;

		void Procedure(const Event& E);

		Input();

	private:
		IVec2 _MousePosition;

		uint32_t _ScrollPosition;

		int8_t _MouseButtons[VOLUND_MOUSE_BUTTON_AMOUNT];
		int8_t _Keys[VOLUND_KEY_AMOUNT];
	};
}
