#include "PCH/PCH.h"
#include "ScriptingEngine.h"

#include "Lua/ScriptingEngine/Script/Script.h"
#include "Lua/ScriptingEngine/ScriptingAPI/ScriptingAPI.h"

#include "Lua/ScriptingEngine/ScriptingAPI/LuaEntity/LuaEntity.h"
#include "Lua/ScriptingEngine/ScriptingAPI/LuaScene/LuaScene.h"

#include <sol/sol.hpp>

namespace Volund
{
	template<typename T, typename>
	T ScriptingEngine::Get(uint64_t scriptId, const std::string& key)
	{
		return (*this->m_LuaState)[scriptId][key];
	}

	template<typename T, typename>
	void ScriptingEngine::Set(uint64_t scriptId, const std::string& key, const T& value)
	{
		(*this->m_LuaState)[scriptId][key] = value;
	}

	template<typename T, typename>
	bool ScriptingEngine::Is(uint64_t scriptId, const std::string& key)
	{
		return (*this->m_LuaState)[scriptId][key].is<T>();
	}

	Ref<Script> ScriptingEngine::LoadScript(const std::string& filepath)
	{		
		sol::table scriptTable;
		sol::protected_function_result result;
		try
		{
			scriptTable = this->m_LuaState->script_file(filepath, [](lua_State*, sol::protected_function_result pfr)
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

		std::vector<std::string> publicVars;
		for (auto& publicVar : scriptTable)
		{
			if (!publicVar.second.is<sol::function>())
			{
				publicVars.push_back(publicVar.first.as<std::string>());
			}
		}

		uint64_t scriptId = this->m_UnusedScriptId;
		this->m_UnusedScriptId++;

		(*this->m_LuaState)[scriptId] = scriptTable;

		m_UnstartedScripts.push_back(scriptId);

		Ref<Script> script = Ref<Script>(new Script(this->shared_from_this(), scriptId, filepath, publicVars));

		return script;
	}

	void ScriptingEngine::ScriptProcedure(uint64_t scriptId, const Event& e)
	{
		switch (e.Type)
		{
		case VOLUND_EVENT_TYPE_UPDATE:
		{
			float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			sol::table script = (*this->m_LuaState)[scriptId];

			for (int i = 0; i < this->m_UnstartedScripts.size(); i++)
			{
				if (this->m_UnstartedScripts[i] == scriptId)
				{
					if (script["OnStart"] != sol::nil)
					{
						script["OnStart"](script);
					}
					this->m_UnstartedScripts.erase(this->m_UnstartedScripts.begin() + i);
					break;
				}
			}

			if (script["OnUpdate"] != sol::nil)
			{
				script["OnUpdate"](script, timeStep);
			}
		}
		break;
		}
	}

	void ScriptingEngine::DestroyScript(uint64_t scriptId)
	{
		sol::table script = (*this->m_LuaState)[scriptId];

		if (script["OnDestroy"] != sol::nil)
		{
			script["OnDestroy"](script);
		}

		(*this->m_LuaState)[scriptId] = sol::nil;
	}

	Ref<ScriptingEngine> ScriptingEngine::Create()
	{
		return Ref<ScriptingEngine>(new ScriptingEngine());
	}

	ScriptingEngine::ScriptingEngine()
	{
		this->m_LuaState = std::make_shared<sol::state>();

		ScriptingAPI::Integrate(this->m_LuaState);
	}

	template LuaInt ScriptingEngine::Get<LuaInt>(uint64_t, const std::string&);
	template LuaFloat ScriptingEngine::Get<LuaFloat>(uint64_t, const std::string&);
	template LuaBool ScriptingEngine::Get<LuaBool>(uint64_t, const std::string&);
	template LuaString ScriptingEngine::Get<LuaString>(uint64_t, const std::string&);
	template LuaVec2 ScriptingEngine::Get<LuaVec2>(uint64_t, const std::string&);
	template LuaVec3 ScriptingEngine::Get<LuaVec3>(uint64_t, const std::string&);
	template Vec4 ScriptingEngine::Get<Vec4>(uint64_t, const std::string&);
	template LuaScene ScriptingEngine::Get<LuaScene>(uint64_t, const std::string&);
	template LuaEntity ScriptingEngine::Get<LuaEntity>(uint64_t, const std::string&);

	template void ScriptingEngine::Set<LuaInt>(uint64_t, const std::string&, const LuaInt&);
	template void ScriptingEngine::Set<LuaFloat>(uint64_t, const std::string&, const LuaFloat&);
	template void ScriptingEngine::Set<LuaBool>(uint64_t, const std::string&, const LuaBool&);
	template void ScriptingEngine::Set<LuaString>(uint64_t, const std::string&, const LuaString&);
	template void ScriptingEngine::Set<LuaVec2>(uint64_t, const std::string&, const LuaVec2&);
	template void ScriptingEngine::Set<LuaVec3>(uint64_t, const std::string&, const LuaVec3&);
	template void ScriptingEngine::Set<Vec4>(uint64_t, const std::string&, const Vec4&);
	template void ScriptingEngine::Set<LuaScene>(uint64_t, const std::string&, const LuaScene&);
	template void ScriptingEngine::Set<LuaEntity>(uint64_t, const std::string&, const LuaEntity&);

	template bool ScriptingEngine::Is<LuaInt>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaFloat>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaBool>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaString>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaVec2>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaVec3>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<Vec4>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaScene>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaEntity>(uint64_t, const std::string&);
}