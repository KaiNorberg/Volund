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

	void Input::HandleEvent(Event* E)
	{
		switch (E->GetType())
		{
		case EventType::KEY:
		{
			KeyEvent* KE = (KeyEvent*)E;
			this->_Keys[KE->GetKey()] += KE->GetIsDown();
			this->_Keys[KE->GetKey()] *= KE->GetIsDown();
			this->_Keys[KE->GetKey()] = Math::Min(this->_Keys[KE->GetKey()], (int8_t)100);
		}
		break;
		case EventType::MOUSE_BUTTON:
		{
			MouseButtonEvent* MBE = (MouseButtonEvent*)E;

			this->_MouseButtons[MBE->GetButton()] += MBE->GetIsDown();
			this->_MouseButtons[MBE->GetButton()] *= MBE->GetIsDown();
			this->_MouseButtons[MBE->GetButton()] = Math::Min(this->_MouseButtons[MBE->GetButton()], (int8_t)100);
		}
		break;
		case EventType::SCROLL:
		{
			ScrollEvent* SE = (ScrollEvent*)E;

			this->_ScrollPosition += SE->GetYOffset();
		}
		break;
		case EventType::MOUSE_MOVE:
		{
			MouseMoveEvent* MME = (MouseMoveEvent*)E;

			this->_MousePosition = IVec2(MME->GetXPos(), MME->GetYPos());
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
