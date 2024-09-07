#pragma once

namespace Volund
{
    template<typename T, typename>
    inline void Script::Set(const std::string& identifier, T value)
    {
        this->m_ScriptingEngine->Set<T>(this->m_ScriptId, identifier, value);
    }

    template<typename T, typename>
    inline bool Script::Is(const std::string& identifier)
    {
        return this->m_ScriptingEngine->Is<T>(this->m_ScriptId, identifier);
    }

    template<typename T, typename>
    inline T Script::Get(const std::string& identifier)
    {
        return this->m_ScriptingEngine->Get<T>(this->m_ScriptId, identifier);
    }
}