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

		Ref<sol::state> m_LuaState;
	};
}