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

	void Script::Procedure(const Event& e)
	{
		this->m_ScriptingEngine->ScriptProcedure(this->m_ScriptId, e);
	}

	Script::~Script()
	{
		this->m_ScriptingEngine->DestroyScript(this->m_ScriptId);
	}

	Script::Script(std::shared_ptr<ScriptingEngine> scriptingEngine, uint64_t scriptId, const std::string& filepath, const std::vector<std::string>& publicVars)
	{
		this->m_ScriptingEngine = scriptingEngine;
		this->m_ScriptId = scriptId;
		this->m_Filepath = filepath;
		this->m_PublicVariables = publicVars;
	}
}
