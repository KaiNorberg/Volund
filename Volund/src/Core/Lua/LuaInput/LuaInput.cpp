#include "PCH/PCH.h"
#include "LuaInput.h"

#include "Core/Scene/Scene.h"

namespace Volund
{
	bool LuaInput::IsHeld(char KeyCode) const
	{
		return Scene::GetInput().IsHeld(KeyCode);
	}

	bool LuaInput::IsPressed(char KeyCode)
	{
		return Scene::GetInput().IsPressed(KeyCode);
	}

	bool LuaInput::IsMouseButtonHeld(char Button) const
	{
		return Scene::GetInput().IsMouseButtonHeld(Button);
	}

	bool LuaInput::IsMouseButtonPressed(char Button)
	{
		return Scene::GetInput().IsMouseButtonPressed(Button);
	}

	uint32_t LuaInput::GetScrollPosition() const
	{
		return Scene::GetInput().GetScrollPosition();
	}

	Vec2 LuaInput::GetMousePosition() const
	{
		return Scene::GetInput().GetMousePosition();
	}
}