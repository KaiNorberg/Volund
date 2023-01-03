#pragma once

#include "Lua/LuaComponent/LuaComponentID.h"

#include "Scene/Scene.h"

namespace Volund
{
	class LuaScene;

	struct LuaEntity
	{
	public:

		int Padding = 0;

		void AddComponent(sol::this_state S, LuaComponentID Component, sol::table Table);

		void DeleteComponent(sol::this_state S, LuaComponentID Component, uint64_t I = 0);

		bool HasComponent(sol::this_state S, LuaComponentID Component);

		uint64_t ComponentAmount(sol::this_state S, LuaComponentID Component);

		sol::table GetScript(sol::this_state S, sol::table Table);

		sol::table GetComponent(sol::this_state S, LuaComponentID Component, uint64_t I = 0);

		LuaEntity(LuaScene* ThisScene, Entity entity);

	private:

		LuaScene* _Scene;

		Entity _Entity;
	};
}