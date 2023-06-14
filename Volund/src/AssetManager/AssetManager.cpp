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

        std::string absolutePath = this->GetAbsolutePath(filepath);

        Ref<Mesh> newMesh = Mesh::CreateAsync(absolutePath);

        return newMesh;
    }

    template<>
    Ref<Texture> AssetManager::Load<Texture>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Texture (%s)...", filepath.c_str());

        std::string absolutePath = this->GetAbsolutePath(filepath);

        Ref<Texture> newTexture = Texture::CreateAsync(absolutePath);

        return newTexture;
    }

    template<>
    Ref<Shader> AssetManager::Load<Shader>(const std::string& filepath)
    {           
        VOLUND_INFO("Loading Shader (%s)...", filepath.c_str());

        std::string absolutePath = this->GetAbsolutePath(filepath);

        Ref<Shader> newShader = Shader::Create(absolutePath);

        return newShader;
    }

    template<>
    Ref<AudioBuffer> AssetManager::Load<AudioBuffer>(const std::string& filepath)
    {
        VOLUND_INFO("Loading AudioBuffer (%s)...", filepath.c_str());

        std::string absolutePath = this->GetAbsolutePath(filepath);

        return std::make_shared<AudioBuffer>(absolutePath);
    }

    template<>
    Ref<Material> AssetManager::Load<Material>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Material (%s)...", filepath.c_str());

        std::string absolutePath = this->GetAbsolutePath(filepath);

        auto materialData = LuaData(absolutePath);

        if (!materialData.Valid())
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

    std::string AssetManager::GetAbsolutePath(const std::string& relativePath)
    {
        if (std::filesystem::exists(relativePath))
        {
            return std::filesystem::relative(relativePath, this->m_ParentPath).string();
        }
        else if (!relativePath.empty() && relativePath[0] == ':')
        {
            return relativePath;
        }
        else
        {
            return this->m_ParentPath + "/" + relativePath;
        }
    }
}