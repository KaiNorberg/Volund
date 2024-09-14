#pragma once

#include "../Component.h"

#include "Lua/ScriptingEngine/Script/Script.h"

namespace Volund
{
    class ScriptComponent : public Component,  public std::enable_shared_from_this<ScriptComponent>
    {
    public:

        bool Valid();

        void SetScript(std::shared_ptr<Script> script);

        std::shared_ptr<Script> GetScript();

        void Procedure(const Event& e) override;

        ScriptComponent();

    private:

        std::shared_ptr<Script> m_Script;
    };
}
