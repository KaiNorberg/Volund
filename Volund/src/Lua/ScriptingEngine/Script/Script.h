#pragma once

#include "../LuaVec/LuaVec.h"

#include "Lua/LuaUtils/LuaUtils.h"

namespace Volund
{
	class ScriptingEngine;

	class Script
	{
	public:

		std::string GetFilepath();

		bool IsPublicVariable(std::string const& identifier);

		const std::vector<std::string>& GetPublicVariables();

		template<typename T>
		T GetVariable(const std::string& identifier);

		template<typename T>
		void SetVariable(const std::string& identifier, T value);

		template<typename T>
		bool IsVariable(const std::string& identifier);

		template <typename... Args>
		void CallFunction(const std::string& name, Args&&... args);

		Script(const std::string& filepath, Ref<ScriptingEngine> scriptingEngine);

	private:

		std::string m_Filepath;

		sol::table m_Table;
		std::vector<std::string> m_PublicVariables;

		Ref<ScriptingEngine> m_ScriptingEngine;
	};

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


	template<typename T>
	inline void Script::SetVariable(const std::string& identifier, T value)
	{
		this->m_Table[identifier] = value;
	}

	template<typename T>
	inline bool Script::IsVariable(const std::string& identifier)
	{
		return this->m_Table[identifier].is<T>();
	}

	template<typename T>
	inline T Script::GetVariable(const std::string& identifier)
	{
		return this->m_Table[identifier];
	}


	template<typename ...Args>
	inline void Script::CallFunction(const std::string& name, Args && ...args)
	{
		if (this->m_Table[name] != sol::nil)
		{
			sol::protected_function_result result;
			try
			{
				result = this->m_Table[name](this->m_Table, args...);
			}
			catch (const sol::error& e)
			{
				VOLUND_WARNING(e.what());
			}
		}
	}
}