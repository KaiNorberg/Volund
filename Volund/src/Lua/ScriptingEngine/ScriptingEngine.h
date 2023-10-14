#pragma once

#include "Dispatcher/Event/Event.h"

#include "Lua/LuaTypes.h"

namespace sol
{
	class state;
}

namespace Volund
{
	class Script;

	class ScriptingEngine : public std::enable_shared_from_this<ScriptingEngine>
	{
	public:

		static inline Logger m_LuaLogger = Logger("LUA");

		template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
		T Get(uint64_t scriptId, const std::string& key);

		template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
		void Set(uint64_t scriptId, const std::string& key, const T& value);

		template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
		bool Is(uint64_t scriptId, const std::string& key);
		
		void ScriptProcedure(uint64_t scriptId, const Event& e);

		Ref<Script> LoadScript(const std::string& filepath);

		void DestroyScript(uint64_t scriptId);

		static Ref<ScriptingEngine> Create();

		ScriptingEngine();

	private:

		std::vector<uint64_t> m_UnstartedScripts;

		uint64_t m_UnusedScriptId = 0;

		Ref<sol::state> m_LuaState;
	};
}