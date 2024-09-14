#include "PCH/PCH.h"
#include "Input.h"

namespace Volund
{
	bool Input::IsHeld(uint16_t keyCode) const
	{
		return (bool)this->m_Keys[keyCode];
	}

	bool Input::IsPressed(uint16_t keyCode)
	{
		const bool isDown = this->m_Keys[keyCode];
		this->m_Keys[keyCode] = false;

		return isDown;
	}

	bool Input::IsMouseButtonHeld(uint16_t button) const
	{
		return (bool)this->m_MouseButtons[button];
	}

	bool Input::IsMouseButtonPressed(uint16_t button)
	{
		const bool isDown = this->m_MouseButtons[button] == 1;
		//this->m_MouseButtons[button] == isDown;

		return isDown;
	}

	float Input::GetScrollPosition() const
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

		switch (e.type)
		{
		case VOLUND_EVENT_KEY:
		{
			const bool isDown = (bool)VOLUND_EVENT_KEY_GET_ISDOWN(e);
			const uint64_t key = VOLUND_EVENT_KEY_GET_KEY(e);

			this->m_Keys[key] = isDown;
		}
		break;
		case VOLUND_EVENT_MOUSE_BUTTON:
		{
			const bool isDown = (bool)VOLUND_EVENT_MOUSE_BUTTON_GET_ISDOWN(e);
			const uint64_t button = VOLUND_EVENT_MOUSE_BUTTON_GET_BUTTON(e);

			this->m_MouseButtons[button] = isDown;
		}
		break;
		case VOLUND_EVENT_MOUSE_WHEEL:
		{
			const float delta = VOLUND_EVENT_MOUSE_WHEEL_GET_DELTA(e);

			this->m_ScrollPosition += delta;
		}
		break;
		case VOLUND_EVENT_MOUSE_MOVE:
		{
			const uint64_t xPos = VOLUND_EVENT_MOUSE_MOVE_GET_XPOS(e);
			const uint64_t yPos = VOLUND_EVENT_MOUSE_MOVE_GET_YPOS(e);

			this->m_MousePosition = IVec2((int32_t)xPos, (int32_t)yPos);
		}
		break;
		default:
		{

		}
		}
	}

	Input::Input()
	{
		memset(this->m_MouseButtons, 0, VOLUND_MOUSE_BUTTON_AMOUNT * sizeof(this->m_MouseButtons[0]));
		memset(this->m_Keys, 0, VOLUND_KEY_AMOUNT * sizeof(this->m_Keys[0]));
	}
}
