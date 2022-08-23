#include "PCH/PCH.h"
#include "Input.h"

#include "Math/Math.h"

namespace Volund
{
	int8_t Input::Keys[KEY_AMOUNT];
	int8_t Input::MouseButtons[MOUSE_BUTTON_AMOUNT];

	bool Input::IsHeld(char KeyCode)
	{
		return Keys[KeyCode];
	}

	bool Input::IsPressed(char KeyCode)
	{
		bool IsDown = Keys[KeyCode] == 1;
		Keys[KeyCode] += IsDown;

		return IsDown;
	}

	bool Input::IsMouseButtonHeld(char Button)
	{
		return MouseButtons[Button];
	}

	bool Input::IsMouseButtonPressed(char Button)
	{
		bool IsDown = MouseButtons[Button] == 1;
		MouseButtons[Button] += IsDown;

		return IsDown;
	}

	void Input::SendKeyEvent(KeyEvent* KE)
	{		
		Keys[KE->GetKey()] += KE->GetIsDown();
		Keys[KE->GetKey()] *= KE->GetIsDown();
		Keys[KE->GetKey()] = Math::Min(Keys[KE->GetKey()], (int8_t)100);
	}

	void Input::SendMouseButtonEvent(MouseButtonEvent* MBE)
	{
		MouseButtons[MBE->GetButton()] += MBE->GetIsDown();
		MouseButtons[MBE->GetButton()] *= MBE->GetIsDown();
		MouseButtons[MBE->GetButton()] = Math::Min(MouseButtons[MBE->GetButton()], (int8_t)100);
	}
}