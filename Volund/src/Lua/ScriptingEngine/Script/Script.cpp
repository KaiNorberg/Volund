#include "PCH/PCH.h"
#include "Script.h"

#include "Lua/ScriptingEngine/ScriptingEngine.h"

namespace Volund
{
	template<>
	inline void Script::SetVariable<Vec4>(const std::string& identifier, Vec4 value)
	{
		this->m_Table[identifier] = LuaVec4(value);
	}

	template<>
	inline bool Script::IsVariable<Vec4>(const std::string& identifier)
	{
		return this->m_Table[identifier].is<LuaVec4>();
	}

	template<>
	inline Vec4 Script::GetVariable<Vec4>(const std::string& identifier)
	{
		return ((LuaVec4)this->m_Table[identifier]).GLM();
	}


	template<>
	inline void Script::SetVariable<Vec3>(const std::string& identifier, Vec3 value)
	{
		this->m_Table[identifier] = LuaVec3(value);
	}

	template<>
	inline bool Script::IsVariable<Vec3>(const std::string& identifier)
	{
		return this->m_Table[identifier].is<LuaVec3>();
	}

	template<>
	inline Vec3 Script::GetVariable<Vec3>(const std::string& identifier)
	{
		return ((LuaVec3)this->m_Table[identifier]).GLM();
	}


	template<>
	inline void Script::SetVariable<Vec2>(const std::string& identifier, Vec2 value)
	{
		this->m_Table[identifier] = LuaVec2(value);
	}

	template<>
	inline bool Script::IsVariable<Vec2>(const std::string& identifier)
	{
		return this->m_Table[identifier].is<LuaVec2>();
	}

	template<>
	inline Vec2 Script::GetVariable<Vec2>(const std::string& identifier)
	{
		return ((LuaVec2)this->m_Table[identifier]).GLM();
	}

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
		this->m_Table = luaState->script_file(filepath);

		for (auto& publicVar : this->m_Table)
		{
			if (!publicVar.second.is<sol::function>())
			{
				this->m_PublicVariables.push_back(publicVar.first.as<std::string>());
			}
		}
	}
}