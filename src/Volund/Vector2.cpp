#include "Vector2.hpp"
#include "Lua/LuaAPI.hpp"

namespace Volund
{
    VOLUND_USERTYPE_REGISTER(Vec2, 
    [](LuaState* state){
        state->NewUsertype<Vec2>("Vec2", 
            sol::constructors<Vec2(), Vec2(float), Vec2(float, float)>(),
            "x", &Vec2::x,
            "y", &Vec2::y,
            "length", &Vec2::Length,
            "length2", &Vec2::Length2,
            "operator+", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a + b; },
                [](const Vec2& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a - b; },
                [](const Vec2& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a * b; },
                [](const Vec2& a, float b) { return a * b; }
            ),
            "operator/", sol::overload(
                [](const Vec2& a, const Vec2& b) { return a / b; },
                [](const Vec2& a, float b) { return a / b; }
            ),
            "operator[]", [](Vec2& v, uint8_t index) { return v[index]; }
        );
    });
}