#include "PCH/PCH.h"
#include "AssetManager.h"

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include "ThreadPool/ThreadPool.h"
#include "ModelLoader/ModelLoader.h"

#include "Scene/Component/Components.h"

#include "Scene/Scene.h"

#include "ImageLoader/ImageLoader.h"

#include "Lua/LuaDeserializer/LuaDeserializer.h"
#include "Lua/LuaSerializer/LuaSerializer.h"

#define VOLUND_SET_COMPONENT(table, member, name) if (table[name] != sol::nil) {member = table[name];}

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
        SoundListener = 9
    };

    template<>
    void AssetManager::Serialize<Material>(Ref<Material> material, const std::string& destinationPath)
    {
        Task task = [this, material, destinationPath]()
        {   
            LuaSerializer serializer = LuaSerializer();

            //IMPORTANT: Remember to update the code below whenever a new component is implemented.

            serializer.StartTable();

            std::string shaderPath = this->FetchFilepath(material->GetShader());
            std::replace(shaderPath.begin(), shaderPath.end(), '\\', '/');
            serializer.Insert("", shaderPath);

            for (auto& [key, value] : material->IntMap())
            {
                serializer.Insert(key, value);
            }

            for (auto& [key, value] : material->FloatMap())
            {
                serializer.Insert(key, value);
            }

            for (auto& [key, value] : material->DoubleMap())
            {
                serializer.Insert(key, value);
            }

            for (auto& [key, value] : material->Vec2Map())
            {
                serializer.Insert(key, value);
            }

            for (auto& [key, value] : material->Vec3Map())
            {
                serializer.Insert(key, value);
            }

            for (auto& [key, value] : material->Vec4Map())
            {
                serializer.Insert(key, value);
            }

            for (auto& [key, value] : material->TextureMap())
            {
                std::string texturePath = this->FetchFilepath(value);
                std::replace(texturePath.begin(), texturePath.end(), '\\', '/');
                serializer.Insert(key, texturePath);
            }

            serializer.EndTable();

            serializer.WriteToFile(destinationPath);
        };

        this->m_Dispatcher->Dispatch(Job(task, nullptr));
    }

    template<>
    void AssetManager::Serialize<Scene>(Ref<Scene> scene, const std::string& destinationPath)
    {
        Task task = [this, scene, destinationPath]()
        {
            LuaSerializer serializer = LuaSerializer();

            //IMPORTANT: Remember to update the code below whenever a new component is implemented.

            serializer.StartTable();
            for (auto& [entity, polyContainer] : (*scene))
            {
                serializer.StartTable();

                for (int i = 0; i < scene->ComponentAmount<Tag>(entity); i++)
                {
                    auto component = scene->GetComponent<Tag>(entity, i);

                    serializer.StartTable();
                    serializer.Insert("ComponentType", (int)LuaComponentID::Tag);
                    serializer.Insert("String", component->String);
                    serializer.EndTable();
                }

                for (int i = 0; i < scene->ComponentAmount<Transform>(entity); i++)
                {
                    auto component = scene->GetComponent<Transform>(entity, i);

                    serializer.StartTable();
                    serializer.Insert("ComponentType", (int)LuaComponentID::Transform);
                    serializer.Insert("Position", component->Position);
                    serializer.Insert("Rotation", component->GetRotation());
                    serializer.Insert("Scale", component->Scale);
                    serializer.EndTable();
                }

                for (int i = 0; i < scene->ComponentAmount<Camera>(entity); i++)
                {
                    auto component = scene->GetComponent<Camera>(entity, i);

                    serializer.StartTable();
                    serializer.Insert("ComponentType", (int)LuaComponentID::Camera);
                    serializer.Insert("FOV", component->FOV);
                    serializer.Insert("NearPlane", component->NearPlane);
                    serializer.Insert("FarPlane", component->FarPlane);
                    //TODO: Insert targetbuffer
                    serializer.EndTable();
                }

                for (int i = 0; i < scene->ComponentAmount<CameraMovement>(entity); i++)
                {
                    auto component = scene->GetComponent<CameraMovement>(entity, i);

                    serializer.StartTable();
                    serializer.Insert("ComponentType", (int)LuaComponentID::CameraMovement);
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
                    serializer.Insert("ComponentType", (int)LuaComponentID::MeshRenderer);
                    serializer.Insert("Mesh", meshPath);
                    serializer.Insert("Material", materialPath);
                    serializer.EndTable();
                }

                for (int i = 0; i < scene->ComponentAmount<PointLight>(entity); i++)
                {
                    auto component = scene->GetComponent<PointLight>(entity, i);

                    serializer.StartTable();
                    serializer.Insert("ComponentType", (int)LuaComponentID::PointLight);
                    serializer.Insert("Color", component->Color);
                    serializer.Insert("Brightness", component->Brightness);
                    serializer.EndTable();
                }

                for (int i = 0; i < scene->ComponentAmount<SoundSource>(entity); i++)
                {
                    auto component = scene->GetComponent<SoundSource>(entity, i);

                    serializer.StartTable();
                    serializer.Insert("ComponentType", (int)LuaComponentID::SoundSource);
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
                    serializer.Insert("ComponentType", (int)LuaComponentID::SoundListener);
                    serializer.EndTable();
                }

                serializer.EndTable();
            }
            serializer.EndTable();

            serializer.WriteToFile(destinationPath);
        };

        this->m_Dispatcher->Dispatch(Job(task, nullptr));
    }

    template<>
    Ref<Scene> AssetManager::Load<Scene>(const std::string& filepath)
    {
        auto scene = std::make_shared<Scene>();

        LuaDeserializer sceneData = LuaDeserializer(filepath);

        if (!sceneData.Valid())
        {
            return scene;
        }

        //IMPORTANT: Remember to update the code below whenever a new component is implemented.

        for (auto& [key, value] : sceneData)
        {
            if (!value.is<sol::table>())
            {
                VOLUND_WARNING("Invalid entity found in scene file!");
                return scene;
            }

            sol::table entityTable = value.as<sol::table>();

            Entity entity = scene->RegisterNewEntity();

            for (auto& [key, value] : entityTable)
            {
                if (!value.is<sol::table>())
                {
                    VOLUND_WARNING("Invalid component found in scene file!");
                    return scene;
                }

                sol::table componentTable = value.as<sol::table>();

                int64_t componentId = componentTable["ComponentType"];

                switch ((LuaComponentID)componentId)
                {
                case LuaComponentID::Transform:
                {
                    auto newComponent = scene->CreateComponent<Transform>(entity);

                    if (componentTable["Position"] != sol::lua_nil)
                    {
                        newComponent->Position = componentTable["Position"];
                    }
                    if (componentTable["Scale"] != sol::lua_nil)
                    {
                        newComponent->Scale = componentTable["Scale"];
                    }
                    if (componentTable["Rotation"] != sol::lua_nil)
                    {
                        Vec3 rotation = componentTable["Rotation"];
                        newComponent->SetRotation(rotation);
                    }
                }
                break;
                case LuaComponentID::Camera:
                {
                    auto newComponent = scene->CreateComponent<Camera>(entity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->FOV, "FOV");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->NearPlane, "NearPlane");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->FarPlane, "FarPlane");

                    if (componentTable["TargetBuffer"] != sol::lua_nil)
                    {
                        //TODO: Add framebuffer asset
                        //newComponent->SetTargetBuffer(componentTable["TargetBuffer"].get<LuaFramebuffer>().Get());
                    }
                }
                break;
                case LuaComponentID::CameraMovement:
                {
                    auto newComponent = scene->CreateComponent<CameraMovement>(entity);

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Speed, "Speed");
                    VOLUND_SET_COMPONENT(componentTable, newComponent->Sensitivity, "Sensitivity");
                }
                break;
                case LuaComponentID::MeshRenderer:
                {
                    if (componentTable["Mesh"] != sol::lua_nil && componentTable["Material"] != sol::lua_nil)
                    {
                        std::string meshFilepath = componentTable["Mesh"];
                        std::string materialFilepath = componentTable["Material"];

                        Ref<Mesh> mesh = this->Fetch<Mesh>(meshFilepath);
                        Ref<Material> material = this->Fetch<Material>(materialFilepath);

                        auto newComponent = scene->CreateComponent<MeshRenderer>(entity, mesh, material);

                        if (componentTable["Layer"] != sol::lua_nil)
                        {
                            newComponent->SetLayer(componentTable["Layer"]);
                        }
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

                    if (componentTable["Color"] != sol::lua_nil)
                    {
                        newComponent->Color = componentTable["Color"];
                    }

                    VOLUND_SET_COMPONENT(componentTable, newComponent->Brightness, "Brightness");
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

                    if (componentTable["Looping"] != sol::lua_nil)
                    {
                        bool looping = componentTable["Looping"];
                        newComponent->SetLooping(looping);
                    }

                    if (componentTable["Pitch"] != sol::lua_nil)
                    {
                        float pitch = componentTable["Pitch"];
                        newComponent->SetPitch(pitch);
                    }

                    if (componentTable["Gain"] != sol::lua_nil)
                    {
                        float gain = componentTable["Gain"];
                        newComponent->SetGain(gain);
                    }

                    if (componentTable["Sound"] != sol::lua_nil)
                    {
                        Ref<AudioBuffer> sound = this->Fetch<AudioBuffer>(componentTable["Sound"]);
                        newComponent->SetBuffer(sound);
                    }

                    if (componentTable["AutoPlay"] != sol::lua_nil)
                    {
                        newComponent->AutoPlay = componentTable["AutoPlay"];
                    }
                }
                break;
                case LuaComponentID::SoundListener:
                {
                    auto newComponent = scene->CreateComponent<SoundListener>(entity);
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

        return scene;
    }

    template<>
    Ref<Material> AssetManager::Load<Material>(const std::string& filepath)
    {
        auto material = Material::Create();

        Task task = [this, material, filepath]()
        {
            auto materialData = LuaDeserializer(filepath);

            if (!materialData.Valid() || materialData.Size() < 1 || !materialData[1].is<std::string>())
            {
                VOLUND_WARNING("Material data is not valid!");
                return material;
            }

            auto shader = this->Fetch<Shader>(materialData[1].as<std::string>());
            material->SetShader(shader);

            bool first = true;

            for (auto& [key, value] : materialData)
            {
                if (first)
                {
                    first = false;
                    continue;
                }

                switch (value.get_type())
                {
                case sol::type::number:
                {
                    if (value.is<int64_t>())
                    {
                        material->SetInt(key.as<std::string>(), (int)value.as<int64_t>());
                    }
                    else if (value.is<double>())
                    {
                        material->SetFloat(key.as<std::string>(), (float)value.as<double>());
                    }
                }
                break;
                case sol::type::userdata:
                {
                    if (value.is<Vec2>())
                    {
                        material->SetVec2(key.as<std::string>(), value.as<Vec2>());
                    }
                    else if (value.is<Vec3>())
                    {
                        material->SetVec3(key.as<std::string>(), value.as<Vec3>());
                    }
                    else if (value.is<Vec4>())
                    {
                        material->SetVec4(key.as<std::string>(), value.as<Vec4>());
                    }
                }
                break;
                case sol::type::string:
                {
                    auto texture = this->Fetch<Texture>(value.as<std::string>());
                    material->SetTexture(key.as<std::string>(), texture);
                }
                break;
                }
            }
        };

        this->m_Dispatcher->Dispatch(Job(task, nullptr));

        return material;
    }

    template<>
    Ref<Mesh> AssetManager::Load<Mesh>(const std::string& filepath)
    {
        Ref<Mesh> newMesh = Mesh::Create();
        Ref<ModelLoader> modelLoader = std::make_shared<ModelLoader>();

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

        Task cleanupTask = [newMesh, modelLoader]()
        {            
            Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(modelLoader->Vertices.data(), modelLoader->Vertices.size());
            vertexBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

            Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(modelLoader->Indices.data(), modelLoader->Indices.size());

            newMesh->SetVertexBuffer(vertexBuffer);
            newMesh->SetIndexBuffer(indexBuffer);
        };

        this->m_Dispatcher->Dispatch(Job(task, cleanupTask));

        return newMesh;
    }

    template<>
    Ref<Texture> AssetManager::Load<Texture>(const std::string& filepath)
    {
        Ref<Texture> newTexture = Texture::Create();

        Ref<ImageLoader> loader = std::make_shared<ImageLoader>();

        Task task = [newTexture, loader, filepath]()
        {
            loader->Load(filepath);
        };

        Task cleanupTask = [newTexture, loader]()
        {
            newTexture->SetData(loader->GetData(), loader->GetWidth(), loader->GetHeight());
        };

        this->m_Dispatcher->Dispatch(Job(task, cleanupTask));

        return newTexture;
    }

    template<>
    Ref<Shader> AssetManager::Load<Shader>(const std::string& filepath)
    {           
        Ref<Shader> newShader = Shader::Create();

        Ref<ShaderLoader> loader = std::make_shared<ShaderLoader>();

        Task task = [newShader, loader, filepath]()
        {
            loader->Load(filepath);
        };

        Task cleanupTask = [newShader, loader]()
        {
            newShader->Init(loader->GetSource(), loader->GetBlueprint());
        };

        this->m_Dispatcher->Dispatch(Job(task, cleanupTask));

        return newShader;
    }

    template<>
    Ref<AudioBuffer> AssetManager::Load<AudioBuffer>(const std::string& filepath)
    {
        auto newAudioBuffer = std::make_shared<AudioBuffer>(filepath);

        return newAudioBuffer;
    }

    std::string AssetManager::GetParentPath()
    {
        return this->m_ParentPath;
    }

    Ref<AssetManager> AssetManager::Create(Ref<Dispatcher> dispatcher, const std::string& parentPath)
    {
        return Ref<AssetManager>(new AssetManager(dispatcher, parentPath));
    }

    AssetManager::AssetManager(Ref<Dispatcher> dispatcher, const std::string& parentPath)
    {
        if (fs::is_directory(parentPath))
        {
            this->m_ParentPath = parentPath;
        }
        else
        {
            this->m_ParentPath = fs::path(parentPath).parent_path().string();
        }

        this->m_Dispatcher = dispatcher;
    }

    std::string AssetManager::GetRelativePath(const std::string& absolutePath)
    {
        if (!absolutePath.empty() && absolutePath[0] == ':')
        {
            return absolutePath;
        }
        else if (fs::exists(absolutePath))
        {
            std::string cleanPath = this->ShortPath(absolutePath);
            return fs::relative(cleanPath, this->m_ParentPath).string();
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
        else if (fs::exists(relativePath))
        {
            std::string cleanPath = this->ShortPath(relativePath);
            return cleanPath;
        }
        else
        {
            std::string cleanPath = this->ShortPath(relativePath);
            return this->m_ParentPath + VOLUND_PATH_SEPERATOR + cleanPath;
        }
    }

    std::string AssetManager::ShortPath(const std::string& path)
    {
        std::string shortPath = path;

        std::replace(shortPath.begin(), shortPath.end(), VOLUND_INVALID_PATH_SEPERATOR, VOLUND_PATH_SEPERATOR);

        return shortPath;
    }
}