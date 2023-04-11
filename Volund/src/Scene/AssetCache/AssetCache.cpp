#include "PCH/PCH.h"
#include "AssetCache.h"

#include "Renderer/Mesh/Mesh.h"
#include "Renderer/Material/Material.h"

#include "Lua/LuaState/LuaAssetLoader/LuaAssetLoader.h"

namespace Volund
{    
    template<>
    Ref<Mesh> AssetCache::PushAsset<Mesh>(const std::string& filepath)
    {   
        auto data = Mesh::Create(filepath);         

        auto newAsset = std::make_shared<Asset<Mesh>>();
        newAsset->Filepath = filepath;
        newAsset->Data = data;
        m_Data.PushBack(newAsset);
        
        return newAsset->Data.lock();
    }

    template<>
    Ref<Texture> AssetCache::PushAsset<Texture>(const std::string& filepath)
    {           
        auto data = Texture::Create(filepath);         

        auto newAsset = std::make_shared<Asset<Texture>>();
        newAsset->Filepath = filepath;
        newAsset->Data = data;
        m_Data.PushBack(newAsset);

        return newAsset->Data.lock();
    }

    template<>
    Ref<Material> AssetCache::PushAsset<Material>(const std::string& filepath)
    {   
        LuaAssetLoader<Material> material = LuaAssetLoader<Material>(this, filepath);        

        auto newAsset = std::make_shared<Asset<Material>>();
        newAsset->Filepath = filepath;
        newAsset->Data = material.Get();
        m_Data.PushBack(newAsset);

        return newAsset->Data.lock();
    }

    AssetCache::AssetCache()
    {
        
    }
}