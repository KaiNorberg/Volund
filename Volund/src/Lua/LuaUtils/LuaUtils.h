#pragma once

//This file should not be included by a .h file, only by .cpp files.

#include "Scene/Scene.h"

#define VOLUND_SET_COMPONENT(table, member, name) if (table[name] != sol::nil) {member = table[name];}

namespace Volund::LuaUtils
{
    Entity DeserializeEntity(Ref<Scene> scene, sol::table entityTable);

    void DeserializeScene(Ref<Scene> scene, sol::table sceneTable);

    sol::protected_function_result ScriptFile(Ref<sol::state> state, const std::string& filepath);
}