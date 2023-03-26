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

		void Procedure(const Event& e);

		void ScriptFile(const std::string& filepath);

		LuaState(Ref<Scene> scene, Ref<Input> input, Ref<Window> window);

		~LuaState();

	private:

		static void LuaPrint(sol::object object);

		static sol::object LuaRequire(sol::this_state s, std::string filepath);

		sol::table LuaComponentView(sol::this_state s, LuaComponentID ComponentID);

		sol::table LuaScriptView(sol::this_state s, sol::table scriptTable);

		template<typename T>
		sol::table GenerateComponentView(sol::this_state s);

		sol::state m_SolState;

		Ref<Scene> m_Scene;
		Ref<Input> m_Input;
		Ref<Window> m_Window;
	};

	template<typename T>
	inline sol::table LuaState::GenerateComponentView(sol::this_state s)
	{
		sol::state_view stateView = s;

		sol::table output = stateView.create_table_with();

		std::vector<Ref<T>> view;
		this->m_Scene->View(view);

		for (auto& component : view)
		{
			output.add(GenerateComponentTable(s, LuaEntity(this->m_Scene, component->GetEntity()), component));
		}

		return output;
	}
}

