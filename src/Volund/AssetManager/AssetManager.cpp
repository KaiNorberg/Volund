#include "PCH/PCH.h"
#include "AssetManager.h"

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include "ModelLoader/ModelLoader.h"

#include "Scene/Component/Components.h"

#include "Scene/Scene.h"

#include "Lua/ScriptingEngine/ScriptingEngine.h"

#include "ImageLoader/ImageLoader.h"

#include "Lua/Deserializer/Deserializer.h"
#include "Lua/Serializer/Serializer.h"

#define VOLUND_SET_COMPONENT(table, member, name, type) if (table.Contains<type>(name)) {member = ((type)table[name]);}
#define VOLUND_SET_COMPONENT_VIA_FUNC(table, func, name, type) if (table.Contains<type>(name)) {func((type)table[name]);}

#define VOLUND_SERIAL_MATERIAL_SHADER "Shader"
#define VOLUND_SERIAL_MATERIAL_UNIFORMS "Uniforms"

namespace Volund
{
    enum class LuaComponentID
    {
        Camera = 1,
        CameraMovement = 2,
        MeshRenderer = 3,
        PointLight = 4,
        //Script = 5,
        Tag = 6,
        Transform = 7,
        SoundSource = 8,
        SoundListener = 9,
        ScriptComponent = 10
    };

    template<>
    void AssetManager::Serialize<Material>(std::shared_ptr<Material> material, const std::string& destinationPath)
    {
        std::string absolutePath = this->GetAbsolutePath(destinationPath);

        Serializer serializer = Serializer(VOLUND_SERIAL_FILE_TYPE_MATERIAL);

        //IMPORTANT: Remember to update the code below whenever a new component is implemented.

        serializer.StartTable();

        std::string shaderPath = this->FetchFilepath(material->GetShader());
        std::replace(shaderPath.begin(), shaderPath.end(), '\\', '/');
        serializer.Insert(VOLUND_SERIAL_MATERIAL_SHADER, shaderPath);

        serializer.StartTable(VOLUND_SERIAL_MATERIAL_UNIFORMS);

        for (auto& uniform : (*material))
        {
            if (uniform->Is<IntUniformType>())
            {
                serializer.Insert(uniform->GetName(), (LuaInt)uniform->As<IntUniformType>());
            }
            else if (uniform->Is<FloatUniformType>())
            {
                serializer.Insert(uniform->GetName(), (LuaFloat)uniform->As<FloatUniformType>());
            }
            else if (uniform->Is<DoubleUniformType>())
            {
                serializer.Insert(uniform->GetName(), (LuaFloat)uniform->As<DoubleUniformType>());
            }
            else if (uniform->Is<Vec2UniformType>())
            {
                serializer.Insert(uniform->GetName(), (LuaVec2)uniform->As<Vec2UniformType>());
            }
            else if (uniform->Is<Vec3UniformType>())
            {
                serializer.Insert(uniform->GetName(), (LuaVec3)uniform->As<Vec3UniformType>());
            }
            else if (uniform->Is<Vec4UniformType>())
            {
                serializer.Insert(uniform->GetName(), (LuaVec4)uniform->As<Vec4UniformType>());
            }
            else if (uniform->Is<TextureUniformType>())
            {
                std::string texturePath = this->FetchFilepath(uniform->As<TextureUniformType>());
                serializer.Insert(uniform->GetName(), texturePath);
            }
        }
        serializer.EndTable();

        serializer.EndTable();

        serializer.WriteToFile(absolutePath);
    }

    template<>
    void AssetManager::Serialize<Scene>(std::shared_ptr<Scene> scene, const std::string& destinationPath)
    {
        std::string absolutePath = this->GetAbsolutePath(destinationPath);

        Serializer serializer = Serializer(VOLUND_SERIAL_FILE_TYPE_SCENE);

        //IMPORTANT: Remember to update the code below whenever a new component is implemented.

        serializer.StartTable();
        for (auto& [entity, polyContainer] : (*scene))
        {
            serializer.StartTable();

            for (int i = 0; i < scene->ComponentAmount<Tag>(entity); i++)
            {
                auto component = scene->GetComponent<Tag>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::Tag);
                serializer.Insert("String", component->String);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<Transform>(entity); i++)
            {
                auto component = scene->GetComponent<Transform>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::Transform);
                serializer.Insert("Position", (LuaVec3)component->Position);
                serializer.Insert("Rotation", (LuaVec3)component->GetRotation());
                serializer.Insert("Scale", (LuaVec3)component->Scale);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<Camera>(entity); i++)
            {
                auto component = scene->GetComponent<Camera>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::Camera);
                serializer.Insert("FOV", component->FOV);
                serializer.Insert("NearPlane", component->NearPlane);
                serializer.Insert("FarPlane", component->FarPlane);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<CameraMovement>(entity); i++)
            {
                auto component = scene->GetComponent<CameraMovement>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::CameraMovement);
                serializer.Insert("Speed", component->Speed);
                serializer.Insert("Sensitivity", component->Sensitivity);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<MeshRenderer>(entity); i++)
            {
                auto component = scene->GetComponent<MeshRenderer>(entity, i);

                std::string meshPath = this->FetchFilepath(component->GetMesh());
                std::replace(meshPath.begin(), meshPath.end(), '\\', '/');

                std::string materialPath = this->FetchFilepath(component->GetMaterial());
                std::replace(materialPath.begin(), materialPath.end(), '\\', '/');

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::MeshRenderer);
                serializer.Insert("Mesh", meshPath);
                serializer.Insert("Material", materialPath);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<PointLight>(entity); i++)
            {
                auto component = scene->GetComponent<PointLight>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::PointLight);
                serializer.Insert("Color", (LuaVec3)component->Color);
                serializer.Insert("Brightness", component->Brightness);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<SoundSource>(entity); i++)
            {
                auto component = scene->GetComponent<SoundSource>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::SoundSource);
                serializer.Insert("Looping", component->GetLooping());
                serializer.Insert("Pitch", component->GetPitch());
                serializer.Insert("Gain", component->GetGain());
                serializer.Insert("AutoPlay", component->AutoPlay);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<SoundListener>(entity); i++)
            {
                auto component = scene->GetComponent<SoundListener>(entity, i);

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::SoundListener);
                serializer.EndTable();
            }

            for (int i = 0; i < scene->ComponentAmount<ScriptComponent>(entity); i++)
            {
                auto component = scene->GetComponent<ScriptComponent>(entity, i);
                std::shared_ptr<Script> script = component->GetScript();

                serializer.StartTable();
                serializer.Insert("ComponentType", (LuaInt)LuaComponentID::ScriptComponent);

                if (script != nullptr)
                {
                    serializer.Insert("Filepath", this->GetRelativePath(script->GetFilepath()));

                    serializer.StartTable("PublicVars");
                    for (const auto& publicVariable : script->GetPublicVariables())
                    {
                        if (script->Is<LuaInt>(publicVariable))
                        {
                            auto rawValue = script->Get<LuaInt>(publicVariable);
                            serializer.Insert(publicVariable, rawValue);
                        }
                        else if (script->Is<LuaFloat>(publicVariable))
                        {
                            auto rawValue = script->Get<LuaFloat>(publicVariable);
                            serializer.Insert(publicVariable, rawValue);
                        }
                        else if (script->Is<LuaString>(publicVariable))
                        {
                            auto rawValue = script->Get<LuaString>(publicVariable);
                            serializer.Insert(publicVariable, rawValue);
                        }
                        else if (script->Is<LuaVec2>(publicVariable))
                        {
                            auto rawValue = script->Get<LuaVec2>(publicVariable);
                            serializer.Insert(publicVariable, rawValue);
                        }
                        else if (script->Is<LuaVec3>(publicVariable))
                        {
                            auto rawValue = script->Get<LuaVec3>(publicVariable);
                            serializer.Insert(publicVariable, rawValue);
                        }
                        else if (script->Is<Vec4>(publicVariable))
                        {
                            auto rawValue = script->Get<Vec4>(publicVariable);
                            serializer.Insert(publicVariable, rawValue);
                        }
                    }
                    serializer.EndTable();
                }

                serializer.EndTable();
            }

            serializer.EndTable();
        }
        serializer.EndTable();

        serializer.WriteToFile(absolutePath);
    }

    template<>
    std::shared_ptr<Scene> AssetManager::Load<Scene>(const std::string& filepath, uint64_t lineId)
    {
        auto scene = Scene::Create();

        Deserializer sceneData = Deserializer(filepath, VOLUND_SERIAL_FILE_TYPE_SCENE);

        if (!sceneData.Valid())
        {
            return scene;
        }

        //IMPORTANT: Remember to update the code below whenever a new component is implemented.

        for (auto& [key, value] : sceneData)
        {
            if (!value->Is<SerialTable>())
            {
                VOLUND_WARNING("Invalid entity found in scene file!");
                return scene;
            }

            SerialTable entityTable = value->As<SerialTable>();

            Entity entity = scene->AllocateEntity();

            for (auto& [key, value] : entityTable)
            {
                if (!value->Is<SerialTable>())
                {
                    VOLUND_WARNING("Invalid component found in scene file!");
                    return scene;
                }

                SerialTable componentTable = value->As<SerialTable>();

                LuaInt componentId = componentTable["ComponentType"];

                switch ((LuaComponentID)componentId)
                {
                case LuaComponentID::Transform:
                {
                    auto newComponent = scene->CreateComponent<Transform>(entity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Position, "Position", Vec3);
                    VOLUND_SET_COMPONENT(componentTable, newComponent->Scale, "Scale", Vec3);
                    VOLUND_SET_COMPONENT_VIA_FUNC(componentTable, newComponent->SetRotation, "Rotation", Vec3);
                }
                break;
                case LuaComponentID::Camera:
                {
                    auto newComponent = scene->CreateComponent<Camera>(entity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->FOV, "FOV", LuaFloat);
                    VOLUND_SET_COMPONENT(componentTable, newComponent->NearPlane, "NearPlane", LuaFloat);
                    VOLUND_SET_COMPONENT(componentTable, newComponent->FarPlane, "FarPlane", LuaFloat);

                    /*if (componentTable["TargetBuffer"] != sol::lua_nil)
                    {
                        //TODO: Add framebuffer asset
                        //newComponent->SetTargetBuffer(componentTable["TargetBuffer"].get<LuaFramebuffer>().Get());
                    }*/
                }
                break;
                case LuaComponentID::CameraMovement:
                {
                    auto newComponent = scene->CreateComponent<CameraMovement>(entity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Speed, "Speed", LuaFloat);
                    VOLUND_SET_COMPONENT(componentTable, newComponent->Sensitivity, "Sensitivity", LuaFloat);
                }
                break;
                case LuaComponentID::MeshRenderer:
                {
                    if (componentTable.Contains<std::string>("Mesh") && componentTable.Contains<std::string>("Material"))
                    {
                        std::string meshFilepath = componentTable["Mesh"];
                        std::string materialFilepath = componentTable["Material"];

                        std::shared_ptr<Mesh> mesh = this->Fetch<Mesh>(meshFilepath);
                        std::shared_ptr<Material> material = this->Fetch<Material>(materialFilepath);

                        auto newComponent = scene->CreateComponent<MeshRenderer>(entity, mesh, material);
                    }
                    else
                    {
                        VOLUND_WARNING("Unable to read mesh or material from MeshRenderer componentTable!");
                    }
                }
                break;
                case LuaComponentID::PointLight:
                {
                    auto newComponent = scene->CreateComponent<PointLight>(entity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Color, "Color", Vec3);
                    VOLUND_SET_COMPONENT(componentTable, newComponent->Brightness, "Brightness", LuaFloat);
                }
                break;
                case LuaComponentID::Tag:
                {
                    std::string string = componentTable["String"];
                    auto newComponent = scene->CreateComponent<Tag>(entity, string);
                }
                break;
                case LuaComponentID::SoundSource:
                {
                    auto newComponent = scene->CreateComponent<SoundSource>(entity);

                    VOLUND_SET_COMPONENT_VIA_FUNC(componentTable, newComponent->SetLooping, "Looping", LuaBool);
                    VOLUND_SET_COMPONENT_VIA_FUNC(componentTable, newComponent->SetPitch, "Pitch", LuaFloat);
                    VOLUND_SET_COMPONENT_VIA_FUNC(componentTable, newComponent->SetGain, "Gain", LuaFloat);
                    VOLUND_SET_COMPONENT(componentTable, newComponent->AutoPlay, "AutoPlay", LuaBool);

                    if (componentTable.Contains<std::string>("Sound"))
                    {
                        std::shared_ptr<AudioBuffer> sound = this->Fetch<AudioBuffer>(componentTable["Sound"]);
                        newComponent->SetBuffer(sound);
                    }
                }
                break;
                case LuaComponentID::SoundListener:
                {
                    auto newComponent = scene->CreateComponent<SoundListener>(entity);
                }
                break;
                case LuaComponentID::ScriptComponent:
                {
                    auto newComponent = scene->CreateComponent<ScriptComponent>(entity);

                    auto script = this->LoadScript(this->GetAbsolutePath(componentTable["Filepath"]));
                    newComponent->SetScript(script);

                    if (componentTable.Contains<SerialTable>("PublicVars"))
                    {
                        SerialTable publicVars = componentTable["PublicVars"];
                        for (auto& [key, value] : publicVars)
                        {
                            if (value->Is<LuaInt>())
                            {
                                script->Set(key, value->As<LuaInt>());
                            }
                            else if (value->Is<LuaFloat>())
                            {
                                script->Set(key, value->As<LuaFloat>());
                            }
                            else if (value->Is<LuaString>())
                            {
                                script->Set(key, value->As<LuaString>());
                            }
                            else if (value->Is<LuaVec2>())
                            {
                                script->Set(key, value->As<LuaVec2>());
                            }
                            else if (value->Is<LuaVec3>())
                            {
                                script->Set(key, value->As<LuaVec3>());
                            }
                            else if (value->Is<Vec4>())
                            {
                                script->Set(key, value->As<Vec4>());
                            }
                        }
                    }
                }
                break;
                default:
                {
                    VOLUND_WARNING("Unknown component id (%s)! Check for proper capitalization and spelling!", componentId);
                }
                break;
                }
            }
        }

        VOLUND_UPDATE_LINE(lineId, "Done ");

        return scene;
    }

    template<>
    std::shared_ptr<Material> AssetManager::Load<Material>(const std::string& filepath, uint64_t lineId)
    {
        auto material = Material::Create();

        Task task = [this, material, filepath, lineId]()
        {
            auto materialData = Deserializer(filepath, VOLUND_SERIAL_FILE_TYPE_MATERIAL);

            if (!materialData.Valid())
            {
                VOLUND_WARNING("Material data is not valid!");
                return;
            }

            std::string shaderFilepath = materialData[VOLUND_SERIAL_MATERIAL_SHADER];
            SerialTable luaUniforms = materialData[VOLUND_SERIAL_MATERIAL_UNIFORMS];

            auto shader = this->Fetch<Shader>(shaderFilepath);

            for (auto& [key, luaUniform] : luaUniforms)
            {
                if (luaUniform->Is<LuaInt>())
                {
                    material->Set(key, (IntUniformType)luaUniform->As<LuaInt>());
                }
                else if (luaUniform->Is<LuaFloat>())
                {
                    material->Set(key, (FloatUniformType)luaUniform->As<LuaFloat>());
                }
                else if (luaUniform->Is<LuaVec2>())
                {
                    material->Set(key, (Vec2UniformType)luaUniform->As<LuaVec2>());
                }
                else if (luaUniform->Is<Vec3>())
                {
                    material->Set(key, luaUniform->As<Vec3>());
                }
                else if (luaUniform->Is<Vec4>())
                {
                    material->Set(key, luaUniform->As<Vec4>());
                }
                else if (luaUniform->Is<LuaString>())
                {
                    auto texture = this->Fetch<Texture>(luaUniform->As<LuaString>());
                    material->Set(key, texture);
                }
            }

            material->SetShader(shader);

            VOLUND_UPDATE_LINE(lineId, "Done ");
        };

        this->m_Dispatcher->Enqueue(Job(task, nullptr));
        //task();

        return material;
    }

    template<>
    std::shared_ptr<Mesh> AssetManager::Load<Mesh>(const std::string& filepath, uint64_t lineId)
    {
        std::shared_ptr<Mesh> newMesh = Mesh::Create();
        std::shared_ptr<ModelLoader> modelLoader = std::make_shared<ModelLoader>();

        Task task = [newMesh, modelLoader, filepath]()
        {
            if (ResourceLibrary::IsResource(filepath))
            {
                modelLoader->ParseOBJ(ResourceLibrary::Fetch(filepath));
            }
            else
            {
                modelLoader->LoadFile(filepath);

                if (!modelLoader->Valid())
                {
                    VOLUND_WARNING("Failed to load mesh %s!", filepath.c_str());
                }
            }
        };

        Task cleanupTask = [newMesh, modelLoader, lineId]()
        {
            std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(modelLoader->Vertices.data(), modelLoader->Vertices.size());
            vertexBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

            std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(modelLoader->Indices.data(), modelLoader->Indices.size());

            newMesh->SetVertexBuffer(vertexBuffer);
            newMesh->SetIndexBuffer(indexBuffer);

            VOLUND_UPDATE_LINE(lineId, "Done ");
        };

        this->m_Dispatcher->Enqueue(Job(task, cleanupTask));
        //task(); cleanupTask();

        return newMesh;
    }

    template<>
    std::shared_ptr<Texture> AssetManager::Load<Texture>(const std::string& filepath, uint64_t lineId)
    {
        std::shared_ptr<Texture> newTexture = Texture::Create();

        std::shared_ptr<ImageLoader> loader = std::make_shared<ImageLoader>();

        Task task = [newTexture, loader, filepath]()
        {
            loader->Load(filepath);
        };

        Task cleanupTask = [newTexture, loader, lineId]()
        {
            newTexture->SetData(loader->GetData(), loader->GetWidth(), loader->GetHeight());

            VOLUND_UPDATE_LINE(lineId, "Done ");
        };

        this->m_Dispatcher->Enqueue(Job(task, cleanupTask));
        //task(); cleanupTask();

        return newTexture;
    }

    template<>
    std::shared_ptr<Shader> AssetManager::Load<Shader>(const std::string& filepath, uint64_t lineId)
    {
        std::shared_ptr<Shader> newShader = Shader::Create();

        std::shared_ptr<ShaderLoader> loader = std::make_shared<ShaderLoader>();

        Task task = [newShader, loader, filepath]()
        {
            loader->Load(filepath);
        };

        Task cleanupTask = [newShader, loader, lineId]()
        {
            newShader->Init(loader->GetSource(), loader->GetBlueprint());

            VOLUND_UPDATE_LINE(lineId, "Done ");
        };

        this->m_Dispatcher->Enqueue(Job(task, cleanupTask));
        //task(); cleanupTask();

        return newShader;
    }

    template<>
    std::shared_ptr<AudioBuffer> AssetManager::Load<AudioBuffer>(const std::string& filepath, uint64_t lineId)
    {
        auto newAudioBuffer = std::make_shared<AudioBuffer>(filepath);

        return newAudioBuffer;
    }

    std::shared_ptr<Script> AssetManager::LoadScript(const std::string& filepath)
    {
        uint64_t lineId = VOLUND_INFO("Loading Script (%s)... ", filepath.c_str());

        if (!this->m_ScriptingEngine.expired())
        {
            auto scriptingEngine = this->m_ScriptingEngine.lock();

            auto newScript = scriptingEngine->LoadScript(filepath);

            VOLUND_UPDATE_LINE(lineId, "Done ");

            return newScript;
        }
        else
        {
            VOLUND_UPDATE_LINE(lineId, "ERROR ");

            return nullptr;
        }
    }

    std::string AssetManager::GetRootDirectory()
    {
        return this->m_RootDir;
    }

    std::shared_ptr<AssetManager> AssetManager::Create(std::shared_ptr<Dispatcher> Dispatcher, const std::string& rootDir, std::shared_ptr<ScriptingEngine> scriptingEngine)
    {
        return std::shared_ptr<AssetManager>(new AssetManager(Dispatcher, rootDir, scriptingEngine));
    }

    std::string AssetManager::GetRelativePath(const std::string& absolutePath)
    {
        if (!absolutePath.empty() && absolutePath[0] == ':')
        {
            return absolutePath;
        }
        else if (std::filesystem::exists(absolutePath))
        {
            std::string cleanPath = this->ShortPath(absolutePath);
            return std::filesystem::relative(cleanPath, this->m_RootDir).string();
        }
        else
        {
            std::string cleanPath = this->ShortPath(absolutePath);
            return cleanPath;
        }
    }

    std::string AssetManager::GetAbsolutePath(const std::string& relativePath)
    {
        if (!relativePath.empty() && relativePath[0] == ':')
        {
            return relativePath;
        }
        else if (std::filesystem::exists(relativePath))
        {
            std::string cleanPath = this->ShortPath(relativePath);
            return cleanPath;
        }
        else
        {
            std::string cleanPath = this->ShortPath(relativePath);
            return this->m_RootDir + VOLUND_PATH_SEPERATOR + cleanPath;
        }
    }

    std::string AssetManager::ShortPath(const std::string& path)
    {
        std::string shortPath = path;

        std::replace(shortPath.begin(), shortPath.end(), VOLUND_INVALID_PATH_SEPERATOR, VOLUND_PATH_SEPERATOR);

        return shortPath;
    }

    AssetManager::AssetManager(std::shared_ptr<Dispatcher> dispatcher, const std::string& rootDir, std::shared_ptr<ScriptingEngine> scriptingEngine)
    {
        if (std::filesystem::is_directory(rootDir))
        {
            this->m_RootDir = rootDir;
        }
        else
        {
            this->m_RootDir = std::filesystem::path(rootDir).parent_path().string();
        }

        this->m_Dispatcher = dispatcher;
        this->m_ScriptingEngine = scriptingEngine;
    }
}
