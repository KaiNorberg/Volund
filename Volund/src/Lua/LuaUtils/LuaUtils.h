#pragma once

#include "SerialTable/SerialTable.h"

namespace Volund::LuaUtils
{
    SerialTable DeserializeTable(sol::table table);

    sol::protected_function_result ScriptFile(Ref<sol::state> state, const std::string& filepath);
}