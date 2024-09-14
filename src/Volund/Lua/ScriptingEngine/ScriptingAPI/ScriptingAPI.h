#pragma once

#include "Lua/ScriptingEngine/ScriptingAPI/ScriptingAPI.h"

namespace sol
{
    class state;
}

namespace Volund::ScriptingAPI
{
    void Integrate(std::shared_ptr<sol::state> state);
}
