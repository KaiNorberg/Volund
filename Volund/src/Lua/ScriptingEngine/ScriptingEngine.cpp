#include "PCH/PCH.h"
#include "ScriptingEngine.h"

#include "LuaVec/LuaVec.h"

namespace Volund
{
	void LuaPrint(sol::object object)
	{
		VOLUND_INFO(object.as<std::string>().c_str());
	}

	void LuaRequire(sol::this_state s, std::string filepath)
	{
		VOLUND_WARNING("Require not implemented!");
	}

	Ref<sol::state> ScriptingEngine::GetLuaState()
	{
		return this->m_LuaState;
	}

	ScriptingEngine::ScriptingEngine()
	{
		this->m_LuaState = std::make_shared<sol::state>();

		this->m_LuaState->open_libraries(sol::lib::base, sol::lib::table);

		(*this->m_LuaState)["require"] = LuaRequire;
		(*this->m_LuaState)["print"] = LuaPrint;

		//Global UserTypes

		//this->m_LuaState->new_usertype<LuaVec4>("Vec4", sol::constructors<void(float, float, float, float)>());

		this->m_LuaState->new_usertype<LuaVec3>("Vec3", sol::constructors<void(float, float, float)>(),
			"X", &LuaVec3::x, "Y", &LuaVec3::y, "Z", &LuaVec3::z);

		//this->m_LuaState->new_usertype<LuaVec2>("Vec2", sol::constructors<void(float, float)>());
	}
}