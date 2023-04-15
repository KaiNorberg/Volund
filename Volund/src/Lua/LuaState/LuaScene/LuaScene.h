#pragma once

#include "../LuaState.h"

#include "Scene/Scene.h"

#include "Window/Window.h"

namespace Volund
{
    class LuaScene : public LuaState
    {
    public:

        Ref<Scene> Get();

        LuaScene(Ref<Window> window, const std::string& filepath);

    private:

        Ref<Scene> m_Scene;
    };
}