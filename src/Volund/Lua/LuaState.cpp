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
        std::string oldCwd = this->m_cwd;
        this->m_cwd = std::filesystem::absolute(filepath).parent_path();

        sol::object newScene = this->m_state.script_file(filepath);        
        if (!newScene.is<std::shared_ptr<Scene>>())
        {
            VOLUND_WARNING("New lua scene handle does not point to a scene");
            this->m_cwd = oldCwd;
            return nullptr;
        }

        this->m_scene = newScene;
        return this->m_scene.as<std::shared_ptr<Scene>>();
    }

    LuaState::LuaState(std::string const& cwd)
    {
        this->m_cwd = std::filesystem::absolute(cwd);

        this->m_state.open_libraries(sol::lib::base);

        this->m_state.set_function("require", [this](std::string const& filepath) {
            return this->m_state.script_file(std::filesystem::path(this->m_cwd) / std::filesystem::path(filepath));
        });

        this->m_state.set_function("print", [this](std::string const& string) {
            VOLUND_INFO(string.c_str());
        });

        this->m_state.new_usertype<Vec3>("Vec3", sol::constructors<Vec3(), Vec3(float), Vec3(float, float, float)>()
        );

        this->m_state.new_usertype<Shader>("Shader", sol::constructors<>(),
            "new", [](std::string const& filepath) { return Shader::Create(filepath); }
        );

        this->m_state.new_usertype<Mesh>("Mesh", sol::constructors<>(),
            "new", [](std::string const& filepath) { return Mesh::Create(filepath); }
        );

        this->m_state.new_usertype<Material>("Material", sol::constructors<>(),
            "new", [](std::shared_ptr<Shader> shader) { return Material::Create(shader); },
            "set_int", [](std::shared_ptr<Material> material, std::string const& name, IntUniformType value)
            {
                material->Set(name, value);
            },
            "set_float", [](std::shared_ptr<Material> material, std::string const& name, FloatUniformType value)
            {
                material->Set(name, value);
            },
            "set_double", [](std::shared_ptr<Material> material, std::string const& name, DoubleUniformType value)
            {
                material->Set(name, value);
            },
            "set_vec2", [](std::shared_ptr<Material> material, std::string const& name, Vec2UniformType value)
            {
                material->Set(name, value);
            },
            "set_vec3", [](std::shared_ptr<Material> material, std::string const& name, Vec3UniformType value)
            {
                material->Set(name, value);
            },
            "set_vec4", [](std::shared_ptr<Material> material, std::string const& name, Vec4UniformType value)
            {
                material->Set(name, value);
            },
            "set_mat4x4", [](std::shared_ptr<Material> material, std::string const& name, Mat4x4UniformType value)
            {
                material->Set(name, value);
            },
            "set_texture", [](std::shared_ptr<Material> material, std::string const& name, TextureUniformType value)
            {
                material->Set(name, value);
            },
            "set_framebuffer", [](std::shared_ptr<Material> material, std::string const& name, FramebufferUniformType value)
            {
                material->Set(name, value);
            }
        );

        this->m_state.new_usertype<Scene>("Scene", sol::constructors<Scene()>(),
            "new", []() { return std::make_shared<Scene>(); },
            "register", &Scene::Register,

            //AddComponent
            "add_camera", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->AddComponent<Camera>(entity);
            },
            "add_mesh_renderer", [](std::shared_ptr<Scene> scene, Entity entity, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
            {
                return scene->AddComponent<MeshRenderer>(entity, mesh, material);
            },
            "add_point_light", [](std::shared_ptr<Scene> scene, Entity entity)
            {
                return scene->AddComponent<PointLight>(entity);
            },            
            "add_transform", [](std::shared_ptr<Scene> scene, Entity entity, Vec3 pos, Vec3 rotation, Vec3 scale)
            {
                return scene->AddComponent<Transform>(entity, pos, rotation, scale);
            }
        );

        this->m_scene = this->m_state.script("return Scene.new()");
    }

    LuaState::~LuaState()
    {
        this->m_scene.reset();
    }

} // namespace Volund
