#include "PCH/PCH.h"
#include "ScriptingAPI.h"

#include "Lua/LuaTypes.h"

#include <sol/sol.hpp>

namespace sol
{
	class state;
}

namespace Volund::ScriptingAPI
{
	Logger luaLogger = Logger("LUA");

	void LuaPrint(sol::object object)
	{
		std::string string = object.as<std::string>();
		luaLogger.Log(LogSeverity::Info, string.c_str());
	}

	void LuaRequire(sol::this_state s, std::string filepath)
	{
		VOLUND_WARNING("Require not implemented!");
	}

	std::string LuaVec4ToString(LuaVec4* vec)
	{
		return std::to_string(vec->x) + ", " + std::to_string(vec->y) + ", " + std::to_string(vec->z) + ", " + std::to_string(vec->w);
	}

	std::string LuaVec3ToString(LuaVec3* vec)
	{
		return std::to_string(vec->x) + ", " + std::to_string(vec->y) + ", " + std::to_string(vec->z);
	}

	std::string LuaVec2ToString(LuaVec2* vec)
	{
		return std::to_string(vec->x) + ", " + std::to_string(vec->y) + ", ";
	}

	void Integrate(std::shared_ptr<sol::state> state)
	{
		//IMPORTANT: Remember to implement new lua components whenever a new component is implemented.

		state->open_libraries(sol::lib::base, sol::lib::table);

		(*state)["require"] = LuaRequire;
		(*state)["print"] = LuaPrint;

		//Global UserTypes

		state->new_usertype<LuaVec4>("Vec4", sol::constructors<void(LuaVec4), void(), void(float), void(float, float, float, float)>(),
			"x", &LuaVec4::x,
			"y", &LuaVec4::y,
			"z", &LuaVec4::z,
			"w", &LuaVec4::w,
			"Length", &LuaVec4::Length,
			"Length2", &LuaVec4::Length2,
			sol::meta_function::to_string, &LuaVec4ToString,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec4(const LuaVec4&) const>(&LuaVec4::operator+), sol::resolve<LuaVec4(const LuaFloat&) const>(&LuaVec4::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec4(const LuaVec4&) const>(&LuaVec4::operator-), sol::resolve<LuaVec4(const LuaFloat&) const>(&LuaVec4::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec4(const LuaVec4&) const>(&LuaVec4::operator*), sol::resolve<LuaVec4(const LuaFloat&) const>(&LuaVec4::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec4(const LuaVec4&) const>(&LuaVec4::operator/), sol::resolve<LuaVec4(const LuaFloat&) const>(&LuaVec4::operator/))
		);

		state->new_usertype<LuaVec3>("Vec3", sol::constructors<void(LuaVec3), void(), void(float), void(float, float, float)>(),
			"x", &LuaVec3::x,
			"y", &LuaVec3::y,
			"z", &LuaVec3::z,
			"Length", &LuaVec3::Length,
			"Length2", &LuaVec3::Length2,
			sol::meta_function::to_string, &LuaVec3ToString,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec3(const LuaVec3&) const>(&LuaVec3::operator+), sol::resolve<LuaVec3(const LuaFloat&) const>(&LuaVec3::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec3(const LuaVec3&) const>(&LuaVec3::operator-), sol::resolve<LuaVec3(const LuaFloat&) const>(&LuaVec3::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec3(const LuaVec3&) const>(&LuaVec3::operator*), sol::resolve<LuaVec3(const LuaFloat&) const>(&LuaVec3::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec3(const LuaVec3&) const>(&LuaVec3::operator/), sol::resolve<LuaVec3(const LuaFloat&) const>(&LuaVec3::operator/))
		);

		state->new_usertype<LuaVec2>("Vec2", sol::constructors<void(LuaVec2), void(), void(float), void(float, float)>(),
			"x", &LuaVec2::x,
			"y", &LuaVec2::y,
			"Length", &LuaVec2::Length,
			"Length2", &LuaVec2::Length2,
			sol::meta_function::to_string, &LuaVec2ToString,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec2(const LuaVec2&) const>(&LuaVec2::operator+), sol::resolve<LuaVec2(const LuaFloat&) const>(&LuaVec2::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec2(const LuaVec2&) const>(&LuaVec2::operator-), sol::resolve<LuaVec2(const LuaFloat&) const>(&LuaVec2::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec2(const LuaVec2&) const>(&LuaVec2::operator*), sol::resolve<LuaVec2(const LuaFloat&) const>(&LuaVec2::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec2(const LuaVec2&) const>(&LuaVec2::operator/), sol::resolve<LuaVec2(const LuaFloat&) const>(&LuaVec2::operator/))
		);

		state->new_usertype<LuaScene>("LuaScene", sol::no_constructor);

		state->new_usertype<LuaEntity>("LuaEntity", sol::no_constructor);
	}
}
