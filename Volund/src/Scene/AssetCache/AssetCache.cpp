#include "PCH/PCH.h"
#include "AssetCache.h"

#include "Rendering/Mesh/Mesh.h"
#include "Rendering/Material/Material.h"

#include "Audio/AudioBuffer/AudioBuffer.h"

#include "Lua/LuaState/LuaAssetLoader/LuaAssetLoader.h"

#include "ThreadPool/ThreadPool.h"
#include "ModelLoader/ModelLoader.h"
#include "ImageLoader/ImageLoader.h"
#include "DeferredTaskHandler/DeferredTaskHandler.h"

namespace Volund
{    
    template<>
    Ref<Mesh> AssetCache::LoadAsset<Mesh>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Mesh %s", filepath.c_str());

        Ref<Mesh> newMesh = Mesh::Create();

        VOLUND_THREADPOOL_SUBMIT([filepath, newMesh]()
        {
            Ref<ModelLoader<float, uint32_t>> loader = std::make_shared<ModelLoader<float, uint32_t>>(filepath);

            DeferredTaskHandler::DeferTask([newMesh, loader]()
            {
                Ref<VertexBuffer> VBuffer = VertexBuffer::Create(loader->Vertices.data(), (uint32_t)loader->Vertices.size());
                VBuffer->SetLayout({ VertexAttributeType::Float3, VertexAttributeType::Float2, VertexAttributeType::Float3 });

                Ref<IndexBuffer> IBuffer = IndexBuffer::Create(loader->Indices.data(), (uint32_t)loader->Indices.size());

                newMesh->SetVertexBuffer(VBuffer);
                newMesh->SetIndexBuffer(IBuffer);
            });
        });

        return newMesh;
    }

    template<>
    Ref<Texture> AssetCache::LoadAsset<Texture>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Texture %s", filepath.c_str());

        Ref<Texture> newTexture = Texture::Create();

        VOLUND_THREADPOOL_SUBMIT([filepath, newTexture]()
        {            
            Ref<ImageLoader> loader = std::make_shared<ImageLoader>(filepath);

            DeferredTaskHandler::DeferTask([newTexture, loader]()
            {
                newTexture->SetData(loader->GetData(), loader->GetWidth(), loader->GetHeight());
            });
        });

        return newTexture;
    }

    template<>
    Ref<Shader> AssetCache::LoadAsset<Shader>(const std::string& filepath)
    {           
        VOLUND_INFO("Loading Shader %s", filepath.c_str());

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

        auto stringStream = std::istringstream(Filesystem::Load(filepath));

        while (std::getline(stringStream, line))
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
    Ref<AudioBuffer> AssetCache::LoadAsset<AudioBuffer>(const std::string& filepath)
    {
        VOLUND_INFO("Loading AudioBuffer %s", filepath.c_str());

        return std::make_shared<AudioBuffer>(filepath);
    }

    template<>
    Ref<Material> AssetCache::LoadAsset<Material>(const std::string& filepath)
    {
        VOLUND_INFO("Loading Material %s", filepath.c_str());

        LuaAssetLoader<Material> material = LuaAssetLoader<Material>(this, filepath);        

        return material.Get();
    }

    AssetCache::AssetCache()
    {
        
    }
}