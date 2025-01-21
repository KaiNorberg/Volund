#include "Lua/LuaState.h"

#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <string>

#include "Component/Components.h"
#include "Lua/LuaAPI.h"

namespace Volund
{
    std::string LuaState::GetCwd()
    {
        return this->m_cwd;
    }

    std::string LuaState::GetSceneFilepath()
    {
        return this->m_sceneFilepath;
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
        VOLUND_LOG_LOADING("scene", filepath);

        std::string oldCwd = this->m_cwd;
        this->m_cwd = std::filesystem::absolute(filepath).parent_path();

        sol::object newScene = this->ScriptFile(filepath);        
        if (!newScene.is<std::shared_ptr<Scene>>())
        {
            VOLUND_LOG_LOADING_FAIL("scene", filepath, "invalid object type");
            this->m_cwd = oldCwd;
            return nullptr;
        }

        this->m_scene = newScene;
        this->m_sceneFilepath = filepath;

        VOLUND_LOG_LOADING_SUCCESS("scene", filepath);
        return this->m_scene.as<std::shared_ptr<Scene>>();
    }

    void LuaState::SaveScene(std::string const& filepath)
    {
        VOLUND_INFO("Saving scene to '{}'", filepath);

        std::unordered_map<Shader*, std::string> shaders;
        std::unordered_map<Texture*, std::string> textures;
        std::unordered_map<Mesh*, std::string> meshes;
        std::unordered_map<Material*, std::string> materials;
        std::unordered_map<AudioBuffer*, std::string> audioBuffers;

        std::string assetSection;
        std::string entitySection;

        sol::global_table globals = this->m_state.globals();
        for (auto& [key, object] : globals)
        {
            std::string string = key.as<std::string>();

            if (object.is<std::shared_ptr<Shader>>())
            {
                std::shared_ptr<Shader> shader = object.as<std::shared_ptr<Shader>>();
                shaders[shader.get()] = string;
                assetSection += string + " = Shader.new(\"" + this->RelativePath(shader->GetFilepath()) + "\")\n";
            }
            else if (object.is<std::shared_ptr<Texture>>())
            {
                std::shared_ptr<Texture> texture = object.as<std::shared_ptr<Texture>>();
                textures[texture.get()] = string;
                assetSection += string + " = Texture.new(\"" + this->RelativePath(texture->GetFilepath()) + "\")\n";
            }
            else if (object.is<std::shared_ptr<Mesh>>())
            {
                std::shared_ptr<Mesh> mesh = object.as<std::shared_ptr<Mesh>>();
                meshes[mesh.get()] = string;
                assetSection += string + " = Mesh.new(\"" + this->RelativePath(mesh->GetFilepath()) + "\")\n";
            }
            else if (object.is<std::shared_ptr<AudioBuffer>>())
            {
                std::shared_ptr<AudioBuffer> audioBuffer = object.as<std::shared_ptr<AudioBuffer>>();
                audioBuffers[audioBuffer.get()] = string;
                assetSection += string + " = AudioBuffer.new(\"" + this->RelativePath(audioBuffer->GetFilepath()) + "\")\n";
            }
        }

        for (auto& [key, object] : globals)
        {
            std::string string = key.as<std::string>();

            if (!object.is<std::shared_ptr<Material>>())
            {
                continue;
            }

            std::shared_ptr<Material> material = object.as<std::shared_ptr<Material>>();
            materials[material.get()] = string;
            std::string shaderKey = shaders[material->GetShader().get()];
            assetSection += string + " = Material.new(" + shaderKey + ")\n";

            for (auto& uniform : (*material))
            {
                assetSection += string + ":";
                if (uniform->Is<IntUniformType>())
                {
                    assetSection += "set_int(\"" + uniform->GetName() + "\", " + std::to_string(uniform->As<IntUniformType>()) + ")\n";
                }
                else if (uniform->Is<FloatUniformType>())
                {
                    assetSection += "set_float(\"" + uniform->GetName() + "\", " + std::to_string(uniform->As<FloatUniformType>()) + ")\n";
                }
                else if (uniform->Is<DoubleUniformType>())
                {
                    assetSection += "set_double(\"" + uniform->GetName() + "\", " + std::to_string(uniform->As<DoubleUniformType>()) + ")\n";
                }
                else if (uniform->Is<Vec2UniformType>())
                {
                    Vec2 vec = uniform->As<Vec2UniformType>();
                    assetSection += "set_vec2(\"" + uniform->GetName() + "\", Vec2.new(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + "))\n";
                }
                else if (uniform->Is<Vec3UniformType>())
                {
                    Vec3 vec = uniform->As<Vec3UniformType>();
                    assetSection += "set_vec3(\"" + uniform->GetName() + "\", Vec3.new(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + "))\n";
                }
                else if (uniform->Is<Vec4UniformType>())
                {
                    Vec4 vec = uniform->As<Vec4UniformType>();
                    assetSection += "set_vec4(\"" + uniform->GetName() + "\", Vec4.new(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ", " + std::to_string(vec.w) + "))\n";
                }
                else if (uniform->Is<Mat4x4UniformType>())
                {
                    Mat4x4 mat = uniform->As<Mat4x4UniformType>();
                    assetSection += "set_mat4x4(\"" + uniform->GetName() + "\", " + "Mat4x4.new{" + 
                        std::to_string(mat[0][0]) + ", " + std::to_string(mat[0][1]) + ", " + std::to_string(mat[0][2]) + ", " + std::to_string(mat[0][3]) + ", " +
                        std::to_string(mat[1][0]) + ", " + std::to_string(mat[1][1]) + ", " + std::to_string(mat[1][2]) + ", " + std::to_string(mat[1][3]) + ", " +
                        std::to_string(mat[2][0]) + ", " + std::to_string(mat[2][1]) + ", " + std::to_string(mat[2][2]) + ", " + std::to_string(mat[2][3]) + ", " +
                        std::to_string(mat[3][0]) + ", " + std::to_string(mat[3][1]) + ", " + std::to_string(mat[3][2]) + ", " + std::to_string(mat[3][3]) + "})\n";
                }
                else if (uniform->Is<TextureUniformType>())
                {
                    std::shared_ptr<Texture> texture = uniform->As<TextureUniformType>();
                    std::string textureKey = textures[texture.get()];
                    assetSection += "set_texture(\"" + uniform->GetName() + "\", " + textureKey + ")\n";
                }
                else if (uniform->Is<FramebufferUniformType>())
                {
                    // TODO: Implement this
                    assetSection += "set_framebuffer()\n";
                }
            }
        }

        std::shared_ptr<Scene> scene = this->SceneRef();

        for (auto& EntityRecord : (*scene))
        {
            std::string key = "e" + std::to_string(EntityRecord.Get().AsInt());
            entitySection += key + " = " + "scene:register()\n";

            for (auto& componentEntry : EntityRecord)
            {
                if (componentEntry.Is<Camera>())
                {
                    std::shared_ptr<Camera> camera = componentEntry.As<Camera>();
                    entitySection += "scene:add_camera(" + key + ", " +
                        std::to_string(camera->fov) + ", " +
                        std::to_string(camera->nearPlane) + ", " +
                        std::to_string(camera->farPlane) + ")\n";
                }
                else if (componentEntry.Is<CameraMovement>())
                {
                    std::shared_ptr<CameraMovement> cameraMovement = componentEntry.As<CameraMovement>();
                    entitySection += "scene:add_camera_movement(" + key + ", " +
                        std::to_string(cameraMovement->speed) + ", " +
                        std::to_string(cameraMovement->sensitivity) + ")\n";
                }
                else if (componentEntry.Is<MeshRenderer>())
                {
                    std::shared_ptr<MeshRenderer> meshRenderer = componentEntry.As<MeshRenderer>();

                    std::string meshKey = meshes[meshRenderer->GetMesh().get()];
                    std::string materialKey = materials[meshRenderer->GetMaterial().get()];

                    entitySection += "scene:add_mesh_renderer(" + key + ", " +
                        meshKey + ", " +
                        materialKey + ")\n";
                }
                else if (componentEntry.Is<PointLight>())
                {
                    std::shared_ptr<PointLight> pointLight = componentEntry.As<PointLight>();

                    entitySection += "scene:add_point_light(" + key + ", Vec3.new(" +
                        std::to_string(pointLight->color.r) + ", " +  std::to_string(pointLight->color.g) + ", " +  std::to_string(pointLight->color.b) + "), " +
                        std::to_string(pointLight->brightness) + ")\n";
                }
                else if (componentEntry.Is<SoundListener>())
                {
                    entitySection += "scene:add_sound_listener(" + key + ")\n";
                }
                else if (componentEntry.Is<SoundSource>())
                {
                    std::shared_ptr<SoundSource> soundSource = componentEntry.As<SoundSource>();

                    std::string audioBufferKey = audioBuffers[soundSource->GetBuffer().get()];

                    entitySection += "scene:add_sound_source(" + key + ", " + audioBufferKey + ")\n";
                }
                else if (componentEntry.Is<Tag>())
                {
                    std::shared_ptr<Tag> tag = componentEntry.As<Tag>();

                    entitySection += "scene:add_tag(" + key + ", \"" + tag->string + "\")\n";
                }
                else if (componentEntry.Is<Transform>())
                {
                    std::shared_ptr<Transform> transform = componentEntry.As<Transform>();

                    Vec3 rotation = transform->GetRotation();

                    entitySection += "scene:add_transform(" + key + ", Vec3.new(" +
                        std::to_string(transform->pos.x) + ", " +  std::to_string(transform->pos.y) + ", " +  std::to_string(transform->pos.z) + "), Vec3.new(" +
                        std::to_string(rotation.x) + ", " +  std::to_string(rotation.y) + ", " +  std::to_string(rotation.z) + "), Vec3.new(" +
                        std::to_string(transform->scale.x) + ", " +  std::to_string(transform->scale.y) + ", " +  std::to_string(transform->scale.z) + "))\n";

                }
            }
        }

        std::ofstream file;
        file.open(filepath);
        if (!file)
        {
            VOLUND_WARNING("Failed to save scene '{}' - failed to open file", filepath);
            return;
        }

        file << "scene = Scene.new()\n";
        file << "--- Assets ---\n";
        file << assetSection;
        file << "--- Entities ---\n";
        file << entitySection;
        file << "return scene\n";
        file.close();

        VOLUND_INFO("Successfully saved scene '{}'", filepath);
    }

    std::string LuaState::AbsolutePath(std::string const& relativePath)
    {
        if (ResourceLibrary::IsResource(relativePath))
        {
            return relativePath;
        }

        return std::filesystem::path(this->m_cwd) / std::filesystem::path(relativePath);
    }

    std::string LuaState::RelativePath(std::string const& absolutePath)
    {
        if (ResourceLibrary::IsResource(absolutePath))
        {
            return absolutePath;
        }

        return std::filesystem::relative(absolutePath, this->m_cwd);
    }


    LuaState::LuaState(std::string const& cwd)
    {
        this->m_cwd = std::filesystem::absolute(cwd);

        LuaAPI::Bind(this);

        this->m_scene = this->m_state.script("return Scene.new()");
    }

    LuaState::~LuaState()
    {
        this->m_scene.reset();
    }
}
