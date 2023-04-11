#pragma once

#include "../LuaState.h"

#include "Renderer/Material/Material.h"

namespace Volund
{
    class LuaMaterial : public LuaState
    {
    public:

        Ref<Material> Get();
        
        LuaMaterial(const std::string& filepath);

        static Ref<LuaMaterial> Create(const std::string& filepath);

    private:

        Ref<Material> m_Material;
    };
}