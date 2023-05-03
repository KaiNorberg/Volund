#pragma once

#include "../LuaState.h"

#include "GameState/GameState.h"

#include "Window/Window.h"

namespace Volund
{
    class LuaGameState : public LuaState
    {
    public:

        Ref<GameState> Get();

        LuaGameState(Ref<Window> window, const std::string& filepath);

    private:

        Ref<GameState> m_GameState;
    };
}