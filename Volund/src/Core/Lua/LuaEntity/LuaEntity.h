#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

#include "Core/Scene/Scene.h"

namespace Volund
{
	struct LuaEntity
	{
	public:

		void AddComponent(sol::this_state S, LuaComponent Component, const sol::table& Table);

		void DeleteComponent(sol::this_state S, LuaComponent Component, uint64_t I = 0);

		sol::object GetComponent(sol::this_state S, LuaComponent Component, uint64_t I = 0);

		void Destroy(sol::this_state S);

		LuaEntity(Scene* ThisScene, Entity entity);

		LuaEntity(Scene* ThisScene);

	private:

		Scene* _Scene;

		Entity _Entity;
	};
}