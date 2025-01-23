#pragma once

#include "Vector3.hpp"
#include "Matrix4x4.hpp"

namespace Volund
{
    class VOLUND_API Quat
    {
    public:
        float w;
        float x;
        float y;
        float z;
        operator Mat4x4() const;
        Vec3 operator*(const Vec3& point) const;
        Quat operator*(const Quat& quaternion) const;
        void operator*=(const Quat& quaternion);
        Vec3 EulerAngles() const;
        float Pitch() const;
        float Yaw() const;
        float Roll() const;
        Quat() = default;
        Quat(const Vec3& eulerAngles);
        Quat(float w, float x, float y, float z);
    private:
    };
}
