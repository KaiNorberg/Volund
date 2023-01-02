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

		LuaEntity CreateEntityWithComponents(sol::this_state S, sol::table Components);

		sol::table ComponentView(sol::this_state S, LuaComponentID Component);

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
			Output.add(GenerateComponentTable(S, Component));
		}

		return Output;
	}
}