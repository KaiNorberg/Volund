#include "PCH/PCH.h"
#include "ScriptComponent.h"

namespace Volund
{
	bool ScriptComponent::ContainsScript()
	{
		return this->m_Script != nullptr;
	}

	void ScriptComponent::SetScript(Ref<Script> script)
	{
		this->m_Script = script;		
	}

	Ref<Script> ScriptComponent::GetScript()
	{
		return this->m_Script;
	}

	void ScriptComponent::Procedure(const Event& e)
	{
		if (this->m_Script != nullptr)
		{
			this->m_Script->Procedure(e);
		}
	}

	ScriptComponent::ScriptComponent()
	{
	}
}