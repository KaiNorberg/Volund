#pragma once

//This file should not be included by a .h file, only by .cpp files.

#include "Scene/Scene.h"

#define VOLUND_SET_COMPONENT(table, member, name) if (table[name] != sol::nil) {member = table[name];}

namespace Volund::LuaUtils
{
    void AddComponentToEntity(Ref<Scene> scene, Entity entity, sol::table componentTable);

    sol::object ScriptFile(Ref<sol::state> state, const std::string& filepath);

    std::string LuaTableToString(sol::table table, int indentation = 0);
}