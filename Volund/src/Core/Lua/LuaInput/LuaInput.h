#pragma once

#include "Input/Input.h"

namespace Volund
{
	struct LuaInput
	{
	public:

		bool IsHeld(char KeyCode) const;
		bool IsPressed(char KeyCode);

		bool IsMouseButtonHeld(char Button) const;
		bool IsMouseButtonPressed(char Button);

		uint32_t GetScrollPosition() const;

		Vec2 GetMousePosition() const;

		LuaInput(Ref<Input> input);

	private:

		Ref<Input> _Input;
	};
}