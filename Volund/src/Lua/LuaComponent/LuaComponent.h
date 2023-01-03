#pragma once

#include "Scene/Component/Components.h"

#include "Lua/LuaEntity/LuaEntity.h"

namespace Volund
{
	template<typename T>
	sol::table GenerateComponentTable(sol::this_state S, const LuaEntity& E, Ref<T> C);
}