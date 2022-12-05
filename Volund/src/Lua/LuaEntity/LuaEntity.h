#pragma once

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaComponent/LuaComponents.h"

#include "Scene/Scene.h"

namespace Volund
{
	struct LuaEntity
	{
	public:

		void AddComponent(LuaComponent Component, const sol::table& Table);

		void DeleteComponent(LuaComponent Component, uint64_t I = 0);

		sol::object GetComponent(sol::this_state S, LuaComponent Component, uint64_t I = 0);

		LuaEntity(Entity Entity);

		LuaEntity();

	private:

		Entity _Entity;
	};
}