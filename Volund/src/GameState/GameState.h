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

		void Procedure(const Event& e);

		GameState(Ref<Window> window);

		~GameState();

	private:

		Ref<Input> m_Input;
		Ref<Scene> m_Scene;
		Ref<LuaState> m_LuaState;
	};
}

