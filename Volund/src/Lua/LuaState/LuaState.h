#pragma once

#define VOLUND_LUA_THIS_SCENE "VOLUND_THIS_SCENE"

#include "EventDispatcher/Event.h"

#include "Input/Input.h"

#include "Time/Time.h"

namespace Volund
{
	class Scene;

	class Window;

	class LuaState
	{
	public:

		static sol::object LuaRequire(sol::this_state S, std::string Filepath);

		static void LuaPrint(std::string String);
		
		Ref<Scene> GetScene();

		void ScriptFile(const std::string& Filepath);

		void Procedure(const Event& E);

		LuaState(Ref<Scene> ThisScene, Ref<Window> ThisWindow);

		~LuaState();

	private:

		void CreateUserTypes();

		sol::state _SolState;

		Ref<Input> _Input;

		Ref<Scene> _ThisScene;
	};
}

