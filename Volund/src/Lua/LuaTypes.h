#pragma once

#include "Math/Math.h"

namespace Volund
{
	using LuaInt = int64_t;
	using LuaFloat = double;
	using LuaBool = bool;
	using LuaString = std::string;
	using LuaVec2 = Vector<2, LuaFloat>;
	using LuaVec3 = Vector<3, LuaFloat>;
	//using LuaVec4 = Vec4;
}

#define VOLUND_TEMPLATE_LUA_TYPES_ONLY typename = std::enable_if_t<std::is_same<T, ::VL::LuaInt>::value || std::is_same<T, ::VL::LuaFloat>::value || \
std::is_same<T, ::VL::LuaBool>::value || std::is_same<T, ::VL::LuaString>::value || \
std::is_same<T, ::VL::LuaVec2>::value || std::is_same<T, ::VL::LuaVec3>::value || \
std::is_same<T, ::VL::Vec4>::value>