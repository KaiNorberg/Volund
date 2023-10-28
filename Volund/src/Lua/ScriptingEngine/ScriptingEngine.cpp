#include "PCH/PCH.h"
#include "ScriptingEngine.h"

#include "Script/Script.h"

#include <sol/sol.hpp>

namespace Volund
{
	void LuaPrint(sol::object object)
	{
		std::string string = object.as<std::string>();
		ScriptingEngine::m_LuaLogger.Log(LogSeverity::Info, string.c_str());
	}

	void LuaRequire(sol::this_state s, std::string filepath)
	{
		VOLUND_WARNING("Require not implemented!");
	}

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
		return (*this->m_LuaState)[scriptId].is<T>();
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

	Ref<ScriptingEngine> ScriptingEngine::Create()
	{
		return std::make_shared<ScriptingEngine>();
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

	ScriptingEngine::ScriptingEngine()
	{
		this->m_LuaState = std::make_shared<sol::state>();

		this->m_LuaState->open_libraries(sol::lib::base, sol::lib::table);

		(*this->m_LuaState)["require"] = LuaRequire;
		(*this->m_LuaState)["print"] = LuaPrint;

		//Global UserTypes

		/*this->m_LuaState->new_usertype<LuaVec4>("Vec4", sol::constructors<void(LuaVec4), void(), void(float), void(float, float, float, float)>(),
			"x", &LuaVec4::x,
			"y", &LuaVec4::y,
			"z", &LuaVec4::z,
			"w", &LuaVec4::w,
			"Length", &LuaVec4::Length,
			"Length2", &LuaVec4::Length2,
			"Normalize", &LuaVec4::Normalize,
			"Reflect", &LuaVec4::Reflect,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator+), sol::resolve<LuaVec4(float)>(&LuaVec4::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator-), sol::resolve<LuaVec4(float)>(&LuaVec4::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator*), sol::resolve<LuaVec4(float)>(&LuaVec4::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec4(const LuaVec4&)>(&LuaVec4::operator/), sol::resolve<LuaVec4(float)>(&LuaVec4::operator/))
		);

		this->m_LuaState->new_usertype<LuaVec3>("Vec3", sol::constructors<void(LuaVec3), void(), void(float), void(float, float, float)>(),
			"x", &LuaVec3::x,
			"y", &LuaVec3::y,
			"z", &LuaVec3::z,
			"Length", &LuaVec3::Length,
			"Length2", &LuaVec3::Length2,
			"Normalize", &LuaVec3::Normalize,
			"Cross", &LuaVec3::Cross,
			"Reflect", &LuaVec3::Reflect,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator+), sol::resolve<LuaVec3(float)>(&LuaVec3::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator-), sol::resolve<LuaVec3(float)>(&LuaVec3::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator*), sol::resolve<LuaVec3(float)>(&LuaVec3::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec3(const LuaVec3&)>(&LuaVec3::operator/), sol::resolve<LuaVec3(float)>(&LuaVec3::operator/))
		);

		this->m_LuaState->new_usertype<LuaVec2>("Vec2", sol::constructors<void(LuaVec2), void(), void(float), void(float, float)>(),
			"x", &LuaVec2::x,
			"y", &LuaVec2::y,
			"Length", &LuaVec2::Length,
			"Length2", &LuaVec2::Length2,
			"Normalize", &LuaVec2::Normalize,
			"Reflect", &LuaVec2::Reflect,
			sol::meta_function::addition, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator+), sol::resolve<LuaVec2(float)>(&LuaVec2::operator+)),
			sol::meta_function::subtraction, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator-), sol::resolve<LuaVec2(float)>(&LuaVec2::operator-)),
			sol::meta_function::multiplication, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator*), sol::resolve<LuaVec2(float)>(&LuaVec2::operator*)),
			sol::meta_function::division, sol::overload(sol::resolve<LuaVec2(const LuaVec2&)>(&LuaVec2::operator/), sol::resolve<LuaVec2(float)>(&LuaVec2::operator/))
		);*/
	}

	template LuaInt ScriptingEngine::Get<LuaInt>(uint64_t, const std::string&);
	template LuaFloat ScriptingEngine::Get<LuaFloat>(uint64_t, const std::string&);
	template LuaBool ScriptingEngine::Get<LuaBool>(uint64_t, const std::string&);
	template LuaString ScriptingEngine::Get<LuaString>(uint64_t, const std::string&);
	template LuaVec2 ScriptingEngine::Get<LuaVec2>(uint64_t, const std::string&);
	template LuaVec3 ScriptingEngine::Get<LuaVec3>(uint64_t, const std::string&);
	template Vec4 ScriptingEngine::Get<Vec4>(uint64_t, const std::string&);

	template void ScriptingEngine::Set<LuaInt>(uint64_t, const std::string&, const LuaInt&);
	template void ScriptingEngine::Set<LuaFloat>(uint64_t, const std::string&, const LuaFloat&);
	template void ScriptingEngine::Set<LuaBool>(uint64_t, const std::string&, const LuaBool&);
	template void ScriptingEngine::Set<LuaString>(uint64_t, const std::string&, const LuaString&);
	template void ScriptingEngine::Set<LuaVec2>(uint64_t, const std::string&, const LuaVec2&);
	template void ScriptingEngine::Set<LuaVec3>(uint64_t, const std::string&, const LuaVec3&);
	template void ScriptingEngine::Set<Vec4>(uint64_t, const std::string&, const Vec4&);

	template bool ScriptingEngine::Is<LuaInt>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaFloat>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaBool>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaString>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaVec2>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<LuaVec3>(uint64_t, const std::string&);
	template bool ScriptingEngine::Is<Vec4>(uint64_t, const std::string&);
}