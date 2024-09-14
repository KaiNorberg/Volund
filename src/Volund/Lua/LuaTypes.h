#pragma once

#include "Math/Math.h"

#include "Lua/ScriptingEngine/ScriptingAPI/LuaEntity/LuaEntity.h"
#include "Lua/ScriptingEngine/ScriptingAPI/LuaScene/LuaScene.h"

namespace Volund
{
    using LuaInt = int64_t;
    using LuaFloat = float;
    using LuaBool = bool;
    using LuaString = std::string;
    using LuaVec2 = Vector<2, LuaFloat>;
    using LuaVec3 = Vector<3, LuaFloat>;
    using LuaVec4 = Vector<4, LuaFloat>;
}

#define VOLUND_TEMPLATE_LUA_TYPES_ONLY typename = std::enable_if_t<std::is_same<T, ::Volund::LuaInt>::value || std::is_same<T, ::Volund::LuaFloat>::value || \
std::is_same<T, ::Volund::LuaBool>::value || std::is_same<T, ::Volund::LuaString>::value || \
std::is_same<T, ::Volund::LuaVec2>::value || std::is_same<T, ::Volund::LuaVec3>::value || \
std::is_same<T, ::Volund::LuaVec4>::value || std::is_same<T, ::Volund::LuaEntity>::value || \
std::is_same<T, ::Volund::LuaScene>::value>
