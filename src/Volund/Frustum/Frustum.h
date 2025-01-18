#pragma once

#include "AABB/AABB.h"

#include <Math/Math.h>

namespace Volund
{
    class Frustum
    {
    public:

        bool ContainsAABB(const AABB& aabb) const;

        Frustum(const Mat4x4& viewProjMatrix);

    private:

        Vec4 m_FrustumPlanes[6];
    };
}
