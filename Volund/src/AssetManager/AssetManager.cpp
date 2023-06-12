#include "PCH/PCH.h"
#include "AssetManager.h"

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include "ThreadPool/ThreadPool.h"
#include "ModelLoader/ModelLoader.h"
#include "ImageLoader/ImageLoader.h"
#include "DeferredTaskHandler/DeferredTaskHandler.h"

#include "Lua/LuaData/LuaData.h"

namespace Volund
{    
    template<>
    Ref<Mesh> AssetManager::Load<Mesh>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Mesh (%s)...", filepath.c_str());

        Ref<Mesh> newMesh = Mesh::Create();

        std::string absolutePath = this->GetAbsolutePath(filepath);

        VOLUND_THREADPOOL_SUBMIT([absolutePath, newMesh]()
        {
            auto modelLoader = std::make_shared<ModelLoader<float, uint32_t>>(absolutePath);

            DeferredTaskHandler::DeferTask([newMesh, modelLoader]()
            {
                Ref<VertexBuffer> VBuffer = VertexBuffer::Create(modelLoader->Vertices.data(), (uint32_t)modelLoader->Vertices.size());
                VBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

                Ref<IndexBuffer> IBuffer = IndexBuffer::Create(modelLoader->Indices.data(), (uint32_t)modelLoader->Indices.size());

                newMesh->SetVertexBuffer(VBuffer);
                newMesh->SetIndexBuffer(IBuffer);
            });
        });

        return newMesh;
    }

    template<>
    Ref<Texture> AssetManager::Load<Texture>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Texture (%s)...", filepath.c_str());

        Ref<Texture> newTexture = Texture::Create();

        std::string absolutePath = this->GetAbsolutePath(filepath);

        VOLUND_THREADPOOL_SUBMIT([absolutePath, newTexture]()
        {            
            Ref<ImageLoader> loader = std::make_shared<ImageLoader>(absolutePath);

            DeferredTaskHandler::DeferTask([newTexture, loader]()
            {
                newTexture->SetData(loader->GetData(), loader->GetWidth(), loader->GetHeight());
            });
        });

        return newTexture;
    }

    template<>
    Ref<Shader> AssetManager::Load<Shader>(const std::string& filepath)
    {           
        VOLUND_INFO("Loading Shader (%s)...", filepath.c_str());

        enum class ShaderType
        {
            None = -1,
            Vertex = 0,
            Fragment = 1,
            Geometry = 2
        };

        std::string line;
        std::stringstream sourceStrings[3];
        ShaderType type = ShaderType::None;

        std::string absolutePath = this->GetAbsolutePath(filepath);

        auto shaderFile = Filesystem::Load(absolutePath);

        if (shaderFile == nullptr)
        {
            VOLUND_ERROR("Failed to load shader %s!", filepath.c_str());
            return nullptr;
        }

        while (shaderFile->GetLine(line))
        {
            //Split into words
            std::vector<std::string> words;
            std::istringstream iss(line);
            std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(),
                std::back_inserter(words));

            if (words.size() <= 0)
            {
                continue;
            }

            if (words.size() >= 2 && words[0] == "#VOLUND_SHADER_TYPE")
            {
                if (words[1] == "VERTEX")
                {
                    type = ShaderType::Vertex;
                }
                else if (words[1] == "FRAGMENT")
                {
                    type = ShaderType::Fragment;
                }
                else if (words[1] == "GEOMETRY")
                {
                    type = ShaderType::Geometry;
                }
            }
            else if ((int32_t)type != -1)
            {
                sourceStrings[(int32_t)type] << line << '\n';
            }
        }

        return Shader::Create(
            sourceStrings[(uint32_t)ShaderType::Vertex].str(),
            sourceStrings[(uint32_t)ShaderType::Fragment].str(),
            sourceStrings[(uint32_t)ShaderType::Geometry].str());
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
            return nullptr;
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
                    material->SetInt(key.as<std::string>(), value.as<int64_t>());
                }
                else if (value.is<double>())
                {
                    material->SetFloat(key.as<std::string>(), value.as<double>());
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
        if (!relativePath.empty() && relativePath[0] == ':')
        {
            return relativePath;
        }
        else
        {
            return this->m_ParentPath + "/" + relativePath;
        }
    }
}