#include "Vector3.hpp"
#include "Lua/LuaAPI.hpp"

namespace Volund
{
    VOLUND_USERTYPE_REGISTER(Vec3, 
    [](LuaState* state){
        state->NewUsertype<Vec3>("Vec3", 
            sol::constructors<Vec3(), Vec3(float), Vec3(float, float, float)>(),
            "x", &Vec3::x,
            "y", &Vec3::y,
            "z", &Vec3::z,
            "length", &Vec3::Length,
            "length2", &Vec3::Length2,
            "operator+", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a + b; },
                [](const Vec3& a, float b) { return a + b; }
            ),
            "operator-", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a - b; },
                [](const Vec3& a, float b) { return a - b; }
            ),
            "operator*", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a * b; },
                [](const Vec3& a, float b) { return a * b; }
            ),
            "operator/", sol::overload(
                [](const Vec3& a, const Vec3& b) { return a / b; },
                [](const Vec3& a, float b) { return a / b; }
            ),
            "operator[]", [](Vec3& v, uint8_t index) { return v[index]; }
        );
    });
}