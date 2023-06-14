#include "PCH/PCH.h"
#include "AssetManager.h"

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include "ThreadPool/ThreadPool.h"
#include "ModelLoader/ModelLoader.h"
#include "DeferredTaskHandler/DeferredTaskHandler.h"

#include "Lua/LuaData/LuaData.h"

namespace Volund
{    
    template<>
    Ref<Mesh> AssetManager::Load<Mesh>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Mesh (%s)...", filepath.c_str());

        Ref<Mesh> newMesh = Mesh::CreateAsync(filepath);

        return newMesh;
    }

    template<>
    Ref<Texture> AssetManager::Load<Texture>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Texture (%s)...", filepath.c_str());

        Ref<Texture> newTexture = Texture::CreateAsync(filepath);

        return newTexture;
    }

    template<>
    Ref<Shader> AssetManager::Load<Shader>(const std::string& filepath)
    {           
        VOLUND_INFO("Loading Shader (%s)...", filepath.c_str());

        Ref<Shader> newShader = Shader::Create(filepath);

        return newShader;
    }

    template<>
    Ref<AudioBuffer> AssetManager::Load<AudioBuffer>(const std::string& filepath)
    {
        VOLUND_INFO("Loading AudioBuffer (%s)...", filepath.c_str());

        return std::make_shared<AudioBuffer>(filepath);
    }

    template<>
    Ref<Material> AssetManager::Load<Material>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Material (%s)...", filepath.c_str());

        auto materialData = LuaData(filepath);

        if (!materialData.Valid() || materialData.Size() < 1 || !materialData[1].is<std::string>())
        {
            VOLUND_WARNING("Material data is not valid!");
            return Material::Create();
        }

        auto shader = this->Fetch<Shader>(materialData[1].as<std::string>());

        auto material = Material::Create(shader);

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

        return material;
    }

    std::string AssetManager::GetParentPath()
    {
        return this->m_ParentPath;
    }

    Ref<AssetManager> AssetManager::Create(const std::string& parentPath)
    {
        return Ref<AssetManager>(new AssetManager(parentPath));
    }

    AssetManager::AssetManager(const std::string& parentPath)
    {
        if (std::filesystem::is_directory(parentPath))
        {
            this->m_ParentPath = parentPath;
        }
        else
        {
            this->m_ParentPath = std::filesystem::path(parentPath).parent_path().string();
        }
    }

    std::string AssetManager::GetRelativePath(const std::string& absolutePath)
    {
        if (std::filesystem::exists(absolutePath))
        {
            return std::filesystem::relative(absolutePath, this->m_ParentPath).string();
        }
        else
        {
            return absolutePath;
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
            return relativePath;
        }
        else
        {
            return this->m_ParentPath + "/" + relativePath;
        }
    }
}