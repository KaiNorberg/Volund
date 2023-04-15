#pragma once

#include "PolyContainer/PolyContainer.h"

namespace Volund
{
    class AssetCache
    {
    public:

        template<typename T>
        Ref<T> Fetch(const std::string& filepath);
        template<typename T>
        std::string FetchFilepath(Ref<T> asset);
        
        AssetCache();

    private:

        std::mutex m_Mutex;

        template<typename T>
        Ref<T> LoadAsset(const std::string& filepath);

        template<typename T>
        void PushAsset(const std::string& filepath, Ref<T> assetData);

        class PrimitiveAsset
        {
        public:
            std::string Filepath;
            
            void* Identifier;

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
    inline Ref<T> AssetCache::Fetch(const std::string& filepath)
    {
        //std::unique_lock lock(this->m_Mutex);

        if (m_Data.Contains<Asset<T>>())
        {
            auto& view = m_Data.View<Asset<T>>();

            for (int i = 0; i < view.size(); i++)
            {
                if (view[i]->Filepath == filepath)
                {
                    auto fetchedData = std::dynamic_pointer_cast<Asset<T>>(view[i])->Data;
                    if (fetchedData.expired())
                    {
                        this->m_Data.Erase<Asset<T>>(i);
                        return this->Fetch<T>(filepath);
                    }

                    return fetchedData.lock();
                }
            }
        }

        Ref<T> newAssetData = this->LoadAsset<T>(filepath);
        this->PushAsset(filepath, newAssetData);

        return newAssetData;
    }

    template<typename T>
    inline std::string AssetCache::FetchFilepath(Ref<T> asset)
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
    inline void AssetCache::PushAsset(const std::string& filepath, Ref<T> assetData)
    {
        auto newAsset = std::make_shared<Asset<T>>();
        newAsset->Filepath = filepath;
        newAsset->Data = assetData;
        newAsset->Identifier = assetData.get();
        this->m_Data.PushBack(newAsset);
    }
}