#pragma once

#include "AABB/AABB.h"

namespace Volund
{
    class Frustum
    {
    public:

		bool ContainsAABB(const AABB& aabb) const;

        Frustum(Mat4x4 ViewProjMatrix);

    private:

        Vec4 _FrustumPlanes[6];
    }; 
}
