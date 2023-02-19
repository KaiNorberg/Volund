#pragma once

#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Lua/LuaState/LuaState.h"

namespace Volund
{
	class GameState
	{
	public:

		Ref<Scene> GetScene();

		Ref<LuaState> GetLuaState();

		void Procedure(const Event& E);

		GameState(Ref<Window> GameWindow);

		~GameState();

	private:

		Ref<Input> _Input;
		Ref<Scene> _Scene;
		Ref<LuaState> _LuaState;
	};
}

