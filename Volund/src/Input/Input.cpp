#include "PCH/PCH.h"
#include "Input.h"

namespace Volund
{
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

	uint32_t Input::GetScrollPosition()
	{
		return ScrollPosition;
	}

	IVec2 Input::GetMousePosition()
	{
		return MousePosition;
	}

	void Input::SendEvent(KeyEvent E)
	{		
		Keys[E.GetKey()] += E.GetIsDown();
		Keys[E.GetKey()] *= E.GetIsDown();
		Keys[E.GetKey()] = Math::Min(Keys[E.GetKey()], (int8_t)100);
	}

	void Input::SendEvent(MouseButtonEvent E)
	{
		MouseButtons[E.GetButton()] += E.GetIsDown();
		MouseButtons[E.GetButton()] *= E.GetIsDown();
		MouseButtons[E.GetButton()] = Math::Min(MouseButtons[E.GetButton()], (int8_t)100);
	}

	void Input::SendEvent(ScrollEvent E)
	{
		ScrollPosition += E.GetYOffset();
	}

	void Input::SendEvent(MouseMoveEvent E)
	{
		MousePosition = DVec2(E.GetXPos(), E.GetYPos());
	}
}