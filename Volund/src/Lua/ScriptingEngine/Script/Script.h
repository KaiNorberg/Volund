#pragma once

#include "../LuaVec/LuaVec.h"

#include "../ScriptingEngine.h"

#include "Dispatcher/Event/Event.h"

namespace Volund
{
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

		void Procedure(const Event& e);

		~Script();

	private:
		friend class ScriptingEngine;

		Script(Ref<ScriptingEngine> scriptingEngine, uint64_t scriptId, const std::string& filepath, const std::vector<std::string>& publicVars);
		
		std::vector<std::string> m_PublicVariables;

		std::string m_Filepath;
		uint64_t m_ScriptId;
		Ref<ScriptingEngine> m_ScriptingEngine;
	};

	template<typename T>
	inline void Script::SetVariable(const std::string& identifier, T value)
	{
		this->m_ScriptingEngine->SetVariable<T>(this->m_ScriptId, identifier, value);
	}

	template<typename T>
	inline bool Script::IsVariable(const std::string& identifier)
	{
		return this->m_ScriptingEngine->IsVariable<T>(this->m_ScriptId, identifier);
	}

	template<typename T>
	inline T Script::GetVariable(const std::string& identifier)
	{
		return this->m_ScriptingEngine->GetVariable<T>(this->m_ScriptId, identifier);
	}
}