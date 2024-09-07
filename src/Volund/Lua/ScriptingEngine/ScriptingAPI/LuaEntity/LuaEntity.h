#pragma once

#include "Scene/Scene.h"

namespace Volund
{
    class LuaEntity
    {
    public:

        LuaEntity(Entity entity, Ref<Scene> scene);

    private:

        Entity m_Entity;
        Ref<Scene> m_Scene;
    };
}