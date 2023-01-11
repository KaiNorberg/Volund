#pragma once

#include "Lua/LuaComponent/LuaComponentID.h"

#include "Scene/Scene.h"

namespace Volund
{
	struct LuaEntity
	{
	public:

		int Padding = NULL;

		Entity Get();

		void AddComponent(sol::this_state S, LuaComponentID ComponentID, sol::table Table);

		void DeleteComponent(sol::this_state S, LuaComponentID ComponentID, uint64_t I = 0);

		bool HasComponent(sol::this_state S, LuaComponentID ComponentID);

		uint64_t ComponentAmount(sol::this_state S, LuaComponentID ComponentID);

		sol::table GetComponent(sol::this_state S, LuaComponentID ComponentID, uint64_t I = 0);

		sol::table GetScript(sol::this_state S, sol::table Table);

		LuaEntity(Ref<Scene> ThisScene, Entity entity);

	private:

		Ref<Scene> _Scene;

		Entity _Entity;
	};
}