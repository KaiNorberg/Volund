#pragma once

#include "PolyContainer/PolyContainer.h"

namespace Volund
{
    class AssetCache
    {
    public:

        template<typename T>
        Ref<T> Fetch(const std::string& filepath);

        AssetCache();

    private:

        class PrimitiveAsset
        {
        public:
            std::string Filepath;
        
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

        //Asset not currently loaded
        VOLUND_INFO("Asset not loaded");

        Ref<T> newAssetData = T::Create(filepath);

        Ref<Asset<T>> newAsset = std::make_shared<Asset<T>>();
        newAsset->Filepath = filepath;
        newAsset->Data = newAssetData;
        m_Data.PushBack(newAsset);

        return newAssetData;
    }
}