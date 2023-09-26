#pragma once

#include "../LuaVec/LuaVec.h"

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

		WeakRef<ScriptingEngine> m_ScriptingEngine;
	};

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
		if (!this->m_ScriptingEngine.expired())
		{
			auto lock = this->m_ScriptingEngine.lock();

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
}