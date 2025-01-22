#pragma once

#include "AABB.hpp"

#include "Math.hpp"

namespace Volund
{
    class VOLUND_API Frustum
    {
    public:
        bool ContainsAABB(const AABB& aabb) const;
        Frustum(const Mat4x4& viewProjMatrix);
    private:
        Vec4 m_frustumPlanes[6];
    };
}
