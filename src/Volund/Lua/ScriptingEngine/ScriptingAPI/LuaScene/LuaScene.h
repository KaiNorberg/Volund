#pragma once

#include "Scene/Scene.h"

namespace Volund
{
    class LuaScene
    {
    public:

        LuaScene(Ref<Scene> scene);

    private:

        Ref<Scene> m_Scene;
    };
}