#include "LuaState.h"

#include <filesystem>

#include "Scene/Component/Components.h"

namespace Volund
{
    std::string LuaState::GetCwd()
    {
        return this->m_cwd;
    }

    sol::protected_function_result LuaState::Script(std::string const& script)
    {
        return this->m_state.safe_script(script);
    }

    sol::protected_function_result LuaState::ScriptFile(std::string const& file)
    {
        return this->m_state.safe_script_file(file);
    }

    std::shared_ptr<Scene> LuaState::SceneRef()
    {
        if (!this->m_scene.is<std::shared_ptr<Scene>>())
        {
            VOLUND_ERROR("Lua scene handle does not point to a scene");
        }

        std::shared_ptr<Scene> scene = this->m_scene.as<std::shared_ptr<Scene>>();
        return scene;
    }

    std::shared_ptr<Scene> LuaState::LoadScene(std::string const& filepath)
    {
        sol::object newScene = this->m_state.script_file(filepath);        
        if (!newScene.is<std::shared_ptr<Scene>>())
        {
            VOLUND_WARNING("New lua scene handle does not point to a scene");
            return nullptr;
        }

        this->m_scene = newScene;
        return this->m_scene.as<std::shared_ptr<Scene>>();
    }

    LuaState::LuaState(std::string const& cwd)
    {
        this->m_cwd = std::filesystem::absolute(cwd);

        this->m_state.open_libraries(sol::lib::base);

        this->m_state.new_usertype<Vec3>("Vec3", sol::constructors<Vec3(), Vec3(float), Vec3(float, float, float)>()
        );

        this->m_state.new_usertype<Mesh>("Mesh", sol::constructors<>(),
            "new", [](std::string const& filepath) { return Mesh::Create(filepath); }
        );

        this->m_state.new_usertype<Scene>("Scene", sol::constructors<Scene()>(),
            "new", []() { return std::make_shared<Scene>(); },
            "register", &Scene::Register,

            //AddComponent
            "add_transform", &Scene::AddComponent<Transform>,
            "add_camera", &Scene::AddComponent<Camera>,
            "add_mesh_renderer", &Scene::AddComponent<MeshRenderer>
        );

        this->m_scene = this->m_state.script("return Scene.new()");
    }

    LuaState::~LuaState()
    {
        this->m_scene.reset();
    }

} // namespace Volund
