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
        template<typename T>
        std::string GetKey(std::shared_ptr<T> object);
        LuaState(std::string const& cwd = ".");
        ~LuaState();
    private:
        friend LuaAPI;
        std::string m_cwd;
        std::string m_sceneFilepath;
        sol::state m_state;
        sol::object m_scene;
    };

    template <typename T> 
    inline std::string LuaState::GetKey(std::shared_ptr<T> object)
    {	
        sol::global_table global = this->m_state.globals();
        for (auto& [key, globalObject] : global)
        {
            if (globalObject.is<std::shared_ptr<T>>())
            {
                if (globalObject.as<std::shared_ptr<T>>() == object)
                {
                    return key.as<std::string>();
                }
            }
        }

        return "";
    }
}