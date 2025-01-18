#pragma once

#include <sol/sol.hpp>

namespace Volund
{
    class LuaState
    {
    public:

        LuaState();

    private:

        sol::state state;
    };
}