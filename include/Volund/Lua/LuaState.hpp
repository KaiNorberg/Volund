#pragma once

#include "../Core.hpp"

#include <sol/sol.hpp>

namespace Volund
{
    class LuaAPI;
    class Scene;

    class VOLUND_API LuaState
    {
    public:
        std::string GetCwd();
        std::string GetSceneFilepath();
        sol::protected_function_result Script(std::string const& script);
        sol::protected_function_result ScriptFile(std::string const& file);
        template<typename T, typename... Args>
		sol::usertype<T> NewUsertype(Args&&... args) {
			return this->m_state.new_usertype<T>(std::forward<Args>(args)...);
		}
        std::shared_ptr<Scene> SceneRef();
        std::shared_ptr<Scene> LoadScene(std::string const& filepath);
        void SaveScene(std::string const& filepath);
        std::string AbsolutePath(std::string const& relativePath);
        std::string RelativePath(std::string const& absolutePath);
        template<typename T>
        std::string GetKey(std::shared_ptr<T> object);
        template<typename T>
        void GetObjects(std::vector<std::pair<std::string, std::shared_ptr<T>>>* out);
        LuaState(std::string const& cwd = ".");
        ~LuaState();
        sol::state m_state;
    private:
        friend LuaAPI;
        std::string m_cwd;
        std::string m_sceneFilepath;
        sol::object m_scene;
    };


#ifdef VOLUND_BUILD
    template <typename T> 
    std::string LuaState::GetKey(std::shared_ptr<T> object)
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

    template<typename T>
    void LuaState::GetObjects(std::vector<std::pair<std::string, std::shared_ptr<T>>>* out)
    {
        sol::global_table globals = this->m_state.globals();
        for (auto& [key, object] : globals)
        {
            if (!object.is<std::shared_ptr<T>>())
            {
                continue;
            }

            out->push_back({key.as<std::string>(), object.as<std::shared_ptr<T>>()});
        }
    }
#endif
}