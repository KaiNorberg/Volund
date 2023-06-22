#pragma once

#include "PolyContainer/PolyContainer.h"

namespace Volund
{
    class AssetManager : public std::enable_shared_from_this<AssetManager>
    {
    public:

        template<typename T>
        Ref<T> Fetch(const std::string& filepath);

        template<typename T>
        std::string FetchFilepath(Ref<T> asset);
        
        template<typename T>
        void Serialize(Ref<T> asset, const std::string& destinationPath);

        std::string GetParentPath();

        static Ref<AssetManager> Create(const std::string& parentPath);

    private:

        AssetManager(const std::string& parentPath);

        std::mutex m_Mutex;

        std::string m_ParentPath;

        std::string GetRelativePath(const std::string& absolutePath);

        std::string GetAbsolutePath(const std::string& relativePath);

        std::string CleanPath(const std::string& path);

        template<typename T>
        Ref<T> Load(const std::string& filepath);

        template<typename T>
        void Push(const std::string& filepath, Ref<T> assetData);

        class PrimitiveAsset
        {
        public:
            std::string Filepath;
            
            void* Identifier = nullptr;

            virtual ~PrimitiveAsset() = default;
        };

        template<typename T>
        class Asset : public PrimitiveAsset
        {
        public:
            WeakRef<T> Data;
        };

        PolyContainer<PrimitiveAsset> m_Data;
    };
    
    template<typename T>
    inline Ref<T> AssetManager::Fetch(const std::string& filepath)
    {
        //std::unique_lock lock(this->m_Mutex);

        std::string absolutePath = this->GetAbsolutePath(filepath);
        std::string relativePath = this->GetRelativePath(filepath);

        if (m_Data.Contains<Asset<T>>())
        {
            auto& view = m_Data.View<Asset<T>>();

            for (int i = 0; i < view.size(); i++)
            {
                if (view[i]->Filepath == relativePath)
                {
                    auto fetchedData = std::dynamic_pointer_cast<Asset<T>>(view[i])->Data;
                    if (fetchedData.expired())
                    {        
                        VOLUND_INFO("Asset expired, retrieving new asset (%s)...", filepath.c_str());
                        this->m_Data.Erase<Asset<T>>(i);
                        return this->Fetch<T>(relativePath);
                    }

                    VOLUND_INFO("Fetching cached asset (%s)...", filepath.c_str());
                    return fetchedData.lock();
                }
            }
        }

        Ref<T> newAssetData = this->Load<T>(absolutePath);
        this->Push(relativePath, newAssetData);

        return newAssetData;
    }

    template<typename T>
    inline std::string AssetManager::FetchFilepath(Ref<T> asset)
    {
        //std::unique_lock lock(this->m_Mutex);

        if (m_Data.Contains<Asset<T>>())
        {
            auto& view = m_Data.View<Asset<T>>();

            for (int i = 0; i < view.size(); i++)
            {
                if (view[i]->Identifier == asset.get())
                {
                    return view[i]->Filepath;
                }
            }
        }

        return "";
    }

    template<typename T>
    inline void AssetManager::Push(const std::string& filepath, Ref<T> assetData)
    {
        auto newAsset = std::make_shared<Asset<T>>();
        newAsset->Filepath = filepath;
        newAsset->Data = assetData;
        newAsset->Identifier = assetData.get();
        this->m_Data.PushBack(newAsset);
    }
}