#pragma once

#define VOLUND_LUA_THIS_SCENE "VOLUND_THIS_SCENE"

#include "EventDispatcher/Event.h"
#include "Input/Input.h"
#include "Time/Time.h"
#include "Scene/Scene.h"

#include "Lua/LuaVec/LuaVec.h"
#include "Lua/LuaEntity/LuaEntity.h"
#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaComponent/LuaComponentID.h"

namespace Volund 
{
	class Window;

	class LuaState
	{
	public:

		void ScriptFile(const std::string& Filepath);

		LuaState(Ref<Scene> ThisScene, Ref<Input> ThisInput, Ref<Window> ThisWindow);

		~LuaState();

	private:

		static void LuaPrint(sol::object Object);

		static sol::object LuaRequire(sol::this_state S, std::string Filepath);

		static sol::table LuaComponentView(sol::this_state S, Ref<Scene> ThisScene, LuaComponentID ComponentID);

		static sol::table LuaScriptView(sol::this_state S, Ref<Scene> ThisScene, sol::table ScriptTable);

		template<typename T>
		static sol::table GenerateComponentView(sol::this_state S, Ref<Scene> ThisScene);

		sol::state _SolState;

		Ref<Scene> _ThisScene;
		Ref<Input> _ThisInput;
		Ref<Window> _ThisWindow;
	};

	template<typename T>
	inline sol::table LuaState::GenerateComponentView(sol::this_state S, Ref<Scene> ThisScene)
	{
		sol::state_view StateView = S;

		sol::table Output = StateView.create_table_with();

		std::vector<Ref<T>> View;
		ThisScene->View(View);

		for (auto& Component : View)
		{
			Output.add(GenerateComponentTable(S, LuaEntity(ThisScene, Component->GetEntity()), Component));
		}

		return Output;
	}
}

