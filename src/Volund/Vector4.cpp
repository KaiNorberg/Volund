#include "Vector4.h"
#include "Lua/LuaAPI.h"

namespace Volund
{
    VOLUND_USERTYPE_REGISTER(Vec4,
    [](LuaState* state){
        state->NewUsertype<Vec4>("Vec4", 
            sol::constructors<Vec4(), Vec4(float), Vec4(float, float, float, float)>(),
            "x", &Vec4::x,
            "y", &Vec4::y,
            "z", &Vec4::z,
            "w", &Vec4::w,
            "length", &Vec4::Length,
            "length2", &Vec4::Length2,
            "operator+", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a + b; },
                [](const Vec4& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a - b; },
                [](const Vec4& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a * b; },
                [](const Vec4& a, float b) { return a * b; }
            ),
            "operator/", sol::overload(
                [](const Vec4& a, const Vec4& b) { return a / b; },
                [](const Vec4& a, float b) { return a / b; }
            ),
            "operator[]", [](Vec4& v, uint8_t index) { return v[index]; }
        );
    });
}