#pragma once

#include "Scene/Scene.h"

#include "Lua/LuaEntity/LuaEntity.h"

#include "Lua/LuaComponent/LuaComponent.h"

namespace Volund
{
	class LuaScene
	{
	public:

		int Padding;

		float TimeSinceStart();

		LuaEntity CreateEntity();

		void DeleteEntity(LuaEntity E);

		void AddComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID, sol::table Table);

		void DeleteComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID, uint64_t I = 0);

		bool HasComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID);

		uint64_t ComponentAmount(sol::this_state S, Entity entity, LuaComponentID ComponentID);

		sol::table GetScript(sol::this_state S, Entity entity, sol::table Table);

		sol::table GetComponent(sol::this_state S, Entity entity, LuaComponentID ComponentID, uint64_t I = 0);

		sol::table ComponentView(sol::this_state S, LuaComponentID ComponentID);

		sol::table ScriptView(sol::this_state S, sol::table ScriptTable);

		LuaScene(Ref<Scene> scene);

	private:

		template<typename T>
		sol::table GenerateComponentView(sol::this_state S);

		Ref<Scene> _Scene;
	};

	template<typename T>
	inline sol::table LuaScene::GenerateComponentView(sol::this_state S)
	{
		sol::state_view StateView = S;
	
		sol::table Output = StateView.create_table_with();

		std::vector<Ref<T>> View;
		this->_Scene->View(View);

		for (auto& Component : View)
		{
			Output.add(GenerateComponentTable(S, LuaEntity(this, Component->GetEntity()), Component));
		}

		return Output;
	}
}