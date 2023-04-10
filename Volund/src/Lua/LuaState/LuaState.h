#pragma once

#define VOLUND_LUA_THIS_SCENE "VOLUND_THIS_SCENE"

namespace sol
{
	class state;
}

namespace Volund 
{
	class Window;

	class LuaState
	{
	public:

		void ScriptFile(const std::string& filepath);

		LuaState();

		virtual ~LuaState();

	protected:

		Ref<sol::state> m_SolState;
	};
}

