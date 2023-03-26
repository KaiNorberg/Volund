#include "PCH/PCH.h"
#include "Input.h"

namespace Volund
{
	bool Input::IsHeld(char keyCode) const
	{
		return (bool)this->m_Keys[keyCode];
	}

	bool Input::IsPressed(char keyCode)
	{
		const bool isDown = this->m_Keys[keyCode] == 1;
		this->m_Keys[keyCode] += isDown;

		return isDown;
	}

	bool Input::IsMouseButtonHeld(char button) const
	{
		return (bool)this->m_MouseButtons[button];
	}

	bool Input::IsMouseButtonPressed(char button)
	{
		const bool isDown = this->m_MouseButtons[button] == 1;
		this->m_MouseButtons[button] += isDown;

		return isDown;
	}

	uint32_t Input::GetScrollPosition() const
	{
		return this->m_ScrollPosition;
	}

	IVec2 Input::GetMousePosition() const
	{
		return this->m_MousePosition;
	}

	void Input::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Key:
		{
			const bool isDown = (bool)VOLUND_EVENT_KEY_GET_ISDOWN(e);
			const uint64_t key = VOLUND_EVENT_KEY_GET_KEY(e);

			this->m_Keys[key] += isDown;
			this->m_Keys[key] *= isDown;
			this->m_Keys[key] = Utils::Min(this->m_Keys[key], (int8_t)100);
		}
		break;
		case EventType::MouseButton:
		{
			const bool isDown = (bool)VOLUND_EVENT_MOUSE_BUTTON_GET_ISDOWN(e);
			const uint64_t button = VOLUND_EVENT_MOUSE_BUTTON_GET_BUTTON(e);

			this->m_MouseButtons[button] += isDown;
			this->m_MouseButtons[button] *= isDown;
			this->m_MouseButtons[button] = Utils::Min(this->m_MouseButtons[button], (int8_t)100);
		}
		break;
		case EventType::MouseWheel:
		{
			const uint64_t delta = VOLUND_EVENT_MOUSE_WHEEL_GET_DELTA(e);

			this->m_ScrollPosition += delta;
		}
		break;
		case EventType::MouseMove:
		{
			const uint64_t xPos = VOLUND_EVENT_MOUSE_MOVE_GET_XPOS(e);
			const uint64_t yPos = VOLUND_EVENT_MOUSE_MOVE_GET_YPOS(e);

			this->m_MousePosition = IVec2(xPos, yPos);
		}
		break;
		}
	}

	Input::Input()
	{
		memset(this->m_MouseButtons, 0, VOLUND_MOUSE_BUTTON_AMOUNT * sizeof(this->m_MouseButtons[0]));
		memset(this->m_Keys, 0, VOLUND_KEY_AMOUNT * sizeof(this->m_Keys[0]));
	}
}
