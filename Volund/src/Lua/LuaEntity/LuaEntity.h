#pragma once

#include "Lua/LuaComponent/LuaComponentID.h"

#include "Scene/Scene.h"

namespace Volund
{
	struct LuaEntity
	{
	public:

		int Padding = 0;

		Entity Get();

		void AddComponent(sol::this_state s, LuaComponentID ComponentID, sol::table table);

		void DeleteComponent(sol::this_state s, LuaComponentID ComponentID, uint64_t index = 0);

		bool HasComponent(sol::this_state s, LuaComponentID ComponentID);

		uint64_t ComponentAmount(sol::this_state s, LuaComponentID ComponentID);

		sol::table GetComponent(sol::this_state s, LuaComponentID ComponentID, uint64_t index = 0);

		sol::table GetScript(sol::this_state s, sol::table table);

		LuaEntity(Ref<Scene> scene, Entity entity);

	private:

		Ref<Scene> m_Scene;

		Entity m_Entity;
	};
}  