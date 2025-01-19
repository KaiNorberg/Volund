#pragma once

#include "Lua/LuaState.h"

namespace Volund
{
    class LuaAPI
    {
    public:
        static void Bind(LuaState* state);
    private:
        LuaAPI() = default;
    };
}