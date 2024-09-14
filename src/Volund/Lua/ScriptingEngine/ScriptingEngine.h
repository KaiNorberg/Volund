#pragma once

#include "Dispatcher/Event.h"

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

        template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
        T Get(uint64_t scriptId, const std::string& key);

        template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
        void Set(uint64_t scriptId, const std::string& key, const T& value);

        template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
        bool Is(uint64_t scriptId, const std::string& key);

        void ScriptProcedure(uint64_t scriptId, const Event& e);

        std::shared_ptr<Script> LoadScript(const std::string& filepath);

        void DestroyScript(uint64_t scriptId);

        static std::shared_ptr<ScriptingEngine> Create();

    private:

        ScriptingEngine();

        std::vector<uint64_t> m_UnstartedScripts;

        uint64_t m_UnusedScriptId = 0;

        std::shared_ptr<sol::state> m_LuaState;
    };
}
