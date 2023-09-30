#pragma once

#include "Script/Script.h"

namespace Volund
{
	class ScriptingEngine
	{
	public:

		Ref<sol::state> GetLuaState();

		ScriptingEngine();

	private:
		
		static void LuaPrint(sol::object object);

		static void LuaRequire(sol::this_state s, std::string filepath);

		static inline Logger m_LuaLogger = Logger("LUA");

		Ref<sol::state> m_LuaState;
	};
}