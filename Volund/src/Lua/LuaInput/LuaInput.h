#pragma once

#include "Input/Input.h"

#include "Lua/LuaVec/LuaVec.h"

namespace Volund
{
	struct LuaInput
	{
	public:

		int Padding;

		bool IsHeld(char KeyCode) const;
		bool IsPressed(char KeyCode);

		bool IsMouseButtonHeld(char Button) const;
		bool IsMouseButtonPressed(char Button);

		uint32_t GetScrollPosition() const;

		LuaVec2 GetMousePosition() const;

		LuaInput(Ref<Input> input);

	private:

		Ref<Input> _Input;
	};
}