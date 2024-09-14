#pragma once

#include "Scene/Scene.h"

namespace Volund
{
    class LuaEntity
    {
    public:

        LuaEntity(Entity entity, std::shared_ptr<Scene> scene);

    private:

        Entity m_Entity;
        std::shared_ptr<Scene> m_Scene;
    };
}
