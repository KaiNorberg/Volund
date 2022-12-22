#include "PCH/PCH.h"
#include "LuaInput.h"

#include "Core/Scene/Scene.h"

namespace Volund
{
	bool LuaInput::IsHeld(char KeyCode) const
	{
		return this->_Input->IsHeld(KeyCode);
	}

	bool LuaInput::IsPressed(char KeyCode)
	{
		return this->_Input->IsPressed(KeyCode);
	}

	bool LuaInput::IsMouseButtonHeld(char Button) const
	{
		return this->_Input->IsMouseButtonHeld(Button);
	}

	bool LuaInput::IsMouseButtonPressed(char Button)
	{
		return this->_Input->IsMouseButtonPressed(Button);
	}

	uint32_t LuaInput::GetScrollPosition() const
	{
		return this->_Input->GetScrollPosition();
	}

	Vec2 LuaInput::GetMousePosition() const
	{
		return this->_Input->GetMousePosition();
	}

	LuaInput::LuaInput(Ref<Input> input)
	{
		this->_Input = input;
	}
}