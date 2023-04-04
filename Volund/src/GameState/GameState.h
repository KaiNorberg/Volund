#pragma once

#include "Input/Input.h"
#include "Scene/Scene.h"
#include "Lua/LuaState/LuaState.h"
#include "Filesystem/Filesystem.h"

namespace Volund
{
	class GameState
	{
	public:

		Ref<Scene> GetScene();

		Ref<LuaState> GetLuaState();

		void Procedure(const Event& e);

		GameState(Ref<Window> window, const std::string& filepath);

		~GameState();

	private:

		Ref<Input> m_Input;
		Ref<Scene> m_Scene;
		Ref<LuaState> m_LuaState;
		Ref<FilesystemLink> m_FilesystemLink;
	};
}

