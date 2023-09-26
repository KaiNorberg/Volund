#pragma once

#include "../Component.h"

#include "Lua/ScriptingEngine/Script/Script.h"

namespace Volund
{
	class ScriptComponent : public Component
	{
	public:

		bool ContainsScript();

		void SetScript(Ref<Script> script);

		Ref<Script> GetScript();

		void OnCreate() override;

		void OnDestroy() override;

		void Procedure(const Event& e) override;

		ScriptComponent();

	private:

		Ref<Script> m_Script;
	};
}