#pragma once

#include "Lua/LuaComponent/LuaComponentID.h"

#include "Scene/Scene.h"

namespace Volund
{
	struct LuaEntity
	{
	public:

		int Padding;

		void AddComponent(sol::this_state S, LuaComponentID Component, const sol::table& Table);

		void DeleteComponent(sol::this_state S, LuaComponentID Component, uint64_t I = 0);

		bool HasComponent(LuaComponentID Component);

		uint64_t ComponentAmount(LuaComponentID Component);

		sol::table GetComponent(sol::this_state S, LuaComponentID Component, uint64_t I = 0);

		void Destroy(sol::this_state S);

		LuaEntity() = default;

		LuaEntity(Scene* ThisScene, Entity entity);

		LuaEntity(Scene* ThisScene);

	private:

		Scene* _Scene;

		Entity _Entity;
	};
}