#pragma once

#include "Lua/LuaComponent/LuaComponent.h"

#include "Scene/Scene.h"

namespace Volund
{
	struct LuaEntity
	{
	public:

		int Padding;

		void AddComponent(sol::this_state S, LuaComponent Component, const sol::table& Table);

		void DeleteComponent(sol::this_state S, LuaComponent Component, uint64_t I = 0);

		sol::object GetComponent(sol::this_state S, LuaComponent Component, uint64_t I = 0);

		void Destroy(sol::this_state S);

		LuaEntity() = default;

		LuaEntity(Scene* ThisScene, Entity entity);

		LuaEntity(Scene* ThisScene);

	private:

		Scene* _Scene;

		Entity _Entity;
	};
}