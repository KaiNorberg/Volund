#pragma once

#include "Scene/Scene.h"

namespace Volund
{
    class LuaScene
    {
    public:

        LuaScene(std::shared_ptr<Scene> scene);

    private:

        std::shared_ptr<Scene> m_Scene;
    };
}
