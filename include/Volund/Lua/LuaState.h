#pragma once

#include "../Scene.h"

#include <sol/sol.hpp>

namespace Volund
{
    class LuaAPI;

    class LuaState
    {
    public:
        std::string GetCwd();
        std::string GetSceneFilepath();
        sol::protected_function_result Script(std::string const& script);
        sol::protected_function_result ScriptFile(std::string const& file);
        std::shared_ptr<Scene> SceneRef();
        std::shared_ptr<Scene> LoadScene(std::string const& filepath);
        void SaveScene(std::string const& filepath);
        std::string AbsolutePath(std::string const& relativePath);
        std::string RelativePath(std::string const& absolutePath);
        LuaState(std::string const& cwd = ".");
        ~LuaState();
    private:
        friend LuaAPI;
        std::string m_cwd;
        std::string m_sceneFilepath;
        sol::state m_state;
        sol::object m_scene;
    };
}