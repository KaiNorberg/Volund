#pragma once

#include "EventDispatcher/Event.h"

namespace Volund
{
	class Input
	{
	public:
		bool IsHeld(char keyCode) const;
		bool IsPressed(char keyCode);

		bool IsMouseButtonHeld(char button) const;
		bool IsMouseButtonPressed(char button);

		uint32_t GetScrollPosition() const;

		IVec2 GetMousePosition() const;

		void Procedure(const Event& e);

		Input();

	private:
		IVec2 m_MousePosition;

		uint32_t m_ScrollPosition;

		bool m_MouseButtons[VOLUND_MOUSE_BUTTON_AMOUNT];
		bool m_Keys[VOLUND_KEY_AMOUNT];
	};
}
