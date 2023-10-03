#include "PCH/PCH.h"
#include "Script.h"

#include "Lua/ScriptingEngine/ScriptingEngine.h"

namespace Volund
{
	std::string Script::GetFilepath()
	{
		return this->m_Filepath;
	}

	bool Script::IsPublicVariable(std::string const& identifier)
	{
		for (auto& publicVar : this->m_PublicVariables)
		{
			if (identifier == publicVar)
			{
				return true;
			}
		}
		return false;
	}

	const std::vector<std::string>& Script::GetPublicVariables()
	{
		return this->m_PublicVariables;
	}

	Script::Script(const std::string& filepath, Ref<ScriptingEngine> scriptingEngine)
	{
		this->m_Filepath = filepath;
		this->m_ScriptingEngine = scriptingEngine;

		auto luaState = scriptingEngine->GetLuaState();
		
		sol::protected_function_result result;
		try
		{
			this->m_Table = luaState->script_file(filepath, [](lua_State*, sol::protected_function_result pfr)
			{
				sol::error err = pfr;
				VOLUND_ERROR(err.what());

				return pfr;
			});
		}
		catch (const sol::error& e)
		{
			VOLUND_ERROR(e.what());
		}

		for (auto& publicVar : this->m_Table)
		{
			if (!publicVar.second.is<sol::function>())
			{
				this->m_PublicVariables.push_back(publicVar.first.as<std::string>());
			}
		}
	}
}