#pragma once

#include "Scene/Scene.h"

#include <sol/sol.hpp>

namespace Volund
{
    class LuaState
    {
    public:

        std::string GetCwd();

        sol::protected_function_result Script(std::string const& script);

        sol::protected_function_result ScriptFile(std::string const& file);

        std::shared_ptr<Scene> SceneRef();

        std::shared_ptr<Scene> LoadScene(std::string const& filepath);

        LuaState(std::string const& cwd = ".");

        ~LuaState();

    private:

        std::string m_cwd;
        sol::state m_state;
        sol::object m_scene;
    };
}