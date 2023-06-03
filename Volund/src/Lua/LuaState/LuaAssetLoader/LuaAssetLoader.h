#pragma once

#include "Rendering/Material/Material.h"

#include "Lua/LuaState/LuaState.h"

namespace Volund
{
    class AssetCache;

    template<typename T>
    class LuaAssetLoader : public LuaState
    {
    public:

        Ref<T> Get();

    private:
        friend class AssetCache;

        LuaAssetLoader(AssetCache* assetCache, const std::string& filepath);

        Ref<T> m_Data;
    };

    template <typename T>
    inline Ref<T> LuaAssetLoader<T>::Get()
    {
        return this->m_Data;
    }
}