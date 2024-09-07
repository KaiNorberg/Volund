#pragma once

namespace Volund
{
    class AABB
    {
    public:

        Vec3 Min;

        Vec3 Max;

        AABB ToWorldSpace(const Mat4x4& modelMatrix);

        AABB() = default;

        AABB(const float points[], const uint32_t count);

        AABB(const std::vector<float>& points);

        AABB(const std::vector<Vec3>& points);

        AABB(Vec3 min, Vec3 max);

    private:
    };
}

