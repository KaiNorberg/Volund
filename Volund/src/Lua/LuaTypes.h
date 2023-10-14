#pragma once

#include "Math/Vec/Vec.h"

namespace Volund
{
	using LuaInt = int64_t;
	using LuaFloat = double;
	using LuaBool = bool;
	using LuaString = std::string;
	using LuaVec2 = Vec<2, LuaFloat>;
	/*using LuaVec3 = Vec3;
	using LuaVec4 = Vec4;*/
}

#define VOLUND_TEMPLATE_LUA_TYPES_ONLY typename = std::enable_if_t<std::is_same<T, LuaInt>::value || std::is_same<T, LuaFloat>::value || \
std::is_same<T, LuaBool>::value || std::is_same<T, LuaString>::value || \
std::is_same<T, LuaVec2>::value || std::is_same<T, Vec3>::value || \
std::is_same<T, Vec4>::value>