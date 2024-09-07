#pragma once

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

        template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
        T Get(const std::string& identifier);

        template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
        void Set(const std::string& identifier, T value);

        template<typename T, VOLUND_TEMPLATE_LUA_TYPES_ONLY>
        bool Is(const std::string& identifier);

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
}

#include "Script_Impl.h"