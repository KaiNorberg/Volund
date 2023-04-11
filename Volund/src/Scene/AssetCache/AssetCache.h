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

        template<typename T>
        Ref<T> PushAsset(const std::string& filepath);

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

        Ref<T> newAssetData = this->PushAsset<T>(filepath);

        return newAssetData;
    }
}