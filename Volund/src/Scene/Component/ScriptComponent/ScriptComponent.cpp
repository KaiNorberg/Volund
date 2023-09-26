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
		
		if (this->m_Script != nullptr)
		{
			this->m_Script->CallFunction("OnCreate");
		}
	}

	Ref<Script> ScriptComponent::GetScript()
	{
		return this->m_Script;
	}

	void ScriptComponent::OnCreate()
	{

	}

	void ScriptComponent::OnDestroy()
	{
		if (this->m_Script != nullptr)
		{
			this->m_Script->CallFunction("OnDestroy");
		}
	}

	void ScriptComponent::Procedure(const Event& e)
	{
		switch (e.Type)
		{
		case VOLUND_EVENT_TYPE_UPDATE:
		{	
			float TS = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			this->m_Script->CallFunction("OnUpdate", TS);
		}
		break;
		}
	}

	ScriptComponent::ScriptComponent()
	{
	}
}