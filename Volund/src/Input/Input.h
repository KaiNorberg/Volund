#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Input
	{
	public:

		bool IsHeld(uint16_t keyCode) const;
		bool IsPressed(uint16_t keyCode);

		bool IsMouseButtonHeld(uint16_t button) const;
		bool IsMouseButtonPressed(uint16_t button);

		float GetScrollPosition() const;

		IVec2 GetMousePosition() const;

		void Procedure(const Event& e);

		Input();

	private:
		IVec2 m_MousePosition;

		float m_ScrollPosition;

		bool m_MouseButtons[VOLUND_MOUSE_BUTTON_AMOUNT];
		bool m_Keys[VOLUND_KEY_AMOUNT];
	};
}
