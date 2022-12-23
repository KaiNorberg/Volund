#include "PCH/PCH.h"
#include "Input.h"

namespace Volund
{
	bool Input::IsHeld(char KeyCode) const
	{
		return (bool)this->_Keys[KeyCode];
	}

	bool Input::IsPressed(char KeyCode)
	{
		bool IsDown = this->_Keys[KeyCode] == 1;
		this->_Keys[KeyCode] += IsDown;

		return IsDown;
	}

	bool Input::IsMouseButtonHeld(char Button) const
	{
		return (bool)this->_MouseButtons[Button];
	}

	bool Input::IsMouseButtonPressed(char Button)
	{
		bool IsDown = this->_MouseButtons[Button] == 1;
		this->_MouseButtons[Button] += IsDown;

		return IsDown;
	}

	uint32_t Input::GetScrollPosition() const
	{
		return this->_ScrollPosition;
	}

	IVec2 Input::GetMousePosition() const
	{
		return this->_MousePosition;
	}

	void Input::HandleEvent(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::KEY:
		{
			bool IsDown = (bool)VOLUND_EVENT_KEY_GET_ISDOWN(E);
			uint64_t Key = VOLUND_EVENT_KEY_GET_KEY(E);

			this->_Keys[Key] += IsDown;
			this->_Keys[Key] *= IsDown;
			this->_Keys[Key] = Utils::Min(this->_Keys[Key], (int8_t)100);
		}
		break;
		case EventType::MOUSE_BUTTON:
		{			
			bool IsDown = (bool)VOLUND_EVENT_MOUSE_BUTTON_GET_ISDOWN(E);
			uint64_t Button = VOLUND_EVENT_MOUSE_BUTTON_GET_BUTTON(E);

			this->_MouseButtons[Button] += IsDown;
			this->_MouseButtons[Button] *= IsDown;
			this->_MouseButtons[Button] = Utils::Min(this->_MouseButtons[Button], (int8_t)100);
		}
		break;
		case EventType::MOUSE_WHEEL:
		{
			uint64_t Delta = VOLUND_EVENT_MOUSE_WHEEL_GET_DELTA(E);

			this->_ScrollPosition += Delta;
		}
		break;
		case EventType::MOUSE_MOVE:
		{			
			uint64_t XPos = VOLUND_EVENT_MOUSE_MOVE_GET_XPOS(E);
			uint64_t YPos = VOLUND_EVENT_MOUSE_MOVE_GET_YPOS(E);

			this->_MousePosition = IVec2(XPos, YPos);
		}
		break;
		}
	}

	Input::Input()
	{
		memset(this->_MouseButtons, 0, VOLUND_MOUSE_BUTTON_AMOUNT * sizeof(this->_MouseButtons[0]));
		memset(this->_Keys, 0, VOLUND_KEY_AMOUNT * sizeof(this->_Keys[0]));
	}
}
