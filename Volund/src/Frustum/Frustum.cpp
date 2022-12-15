#include "PCH/PCH.h"
#include "Frustum.h"

namespace Volund
{
	bool Frustum::ContainsAABB(const AABB& aabb) const
	{
		Vec4 axisVert(1.0f);

		for (int32_t y = 0; y < 6; y++)
		{
			// x-axis
			if (_FrustumPlanes[y].x < 0.0f)
			{
				axisVert.x = aabb.Min.x;
			}
			else
			{
				axisVert.x = aabb.Max.x;
			}

			// y-axis
			if (_FrustumPlanes[y].y < 0.0f)
			{
				axisVert.y = aabb.Min.y;
			}
			else
			{
				axisVert.y = aabb.Max.y;
			}

			// z-axis
			if (_FrustumPlanes[y].z < 0.0f)
			{
				axisVert.z = aabb.Min.z;
			}
			else
			{
				axisVert.z = aabb.Max.z;
			}

			if (glm::dot(_FrustumPlanes[y], axisVert) < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

	Frustum::Frustum(Mat4x4 ViewProjMatrix)
	{
		// Left clipping plane
		_FrustumPlanes[0].x = ViewProjMatrix[0][3] + ViewProjMatrix[0][0];
		_FrustumPlanes[0].y = ViewProjMatrix[1][3] + ViewProjMatrix[1][0];
		_FrustumPlanes[0].z = ViewProjMatrix[2][3] + ViewProjMatrix[2][0];
		_FrustumPlanes[0].w = ViewProjMatrix[3][3] + ViewProjMatrix[3][0];
		// Right clipping plane
		_FrustumPlanes[1].x = ViewProjMatrix[0][3] - ViewProjMatrix[0][0];
		_FrustumPlanes[1].y = ViewProjMatrix[1][3] - ViewProjMatrix[1][0];
		_FrustumPlanes[1].z = ViewProjMatrix[2][3] - ViewProjMatrix[2][0];
		_FrustumPlanes[1].w = ViewProjMatrix[3][3] - ViewProjMatrix[3][0];
		// Top clipping plane
		_FrustumPlanes[2].x = ViewProjMatrix[0][3] - ViewProjMatrix[0][1];
		_FrustumPlanes[2].y = ViewProjMatrix[1][3] - ViewProjMatrix[1][1];
		_FrustumPlanes[2].z = ViewProjMatrix[2][3] - ViewProjMatrix[2][1];
		_FrustumPlanes[2].w = ViewProjMatrix[3][3] - ViewProjMatrix[3][1];
		// Bottom clipping plane
		_FrustumPlanes[3].x = ViewProjMatrix[0][3] + ViewProjMatrix[0][1];
		_FrustumPlanes[3].y = ViewProjMatrix[1][3] + ViewProjMatrix[1][1];
		_FrustumPlanes[3].z = ViewProjMatrix[2][3] + ViewProjMatrix[2][1];
		_FrustumPlanes[3].w = ViewProjMatrix[3][3] + ViewProjMatrix[3][1];
		// Near clipping plane
		_FrustumPlanes[4].x = ViewProjMatrix[0][2];
		_FrustumPlanes[4].y = ViewProjMatrix[1][2];
		_FrustumPlanes[4].z = ViewProjMatrix[2][2];
		_FrustumPlanes[4].w = ViewProjMatrix[3][2];
		// Far clipping plane
		_FrustumPlanes[5].x = ViewProjMatrix[0][3] - ViewProjMatrix[0][2];
		_FrustumPlanes[5].y = ViewProjMatrix[1][3] - ViewProjMatrix[1][2];
		_FrustumPlanes[5].z = ViewProjMatrix[2][3] - ViewProjMatrix[2][2];
		_FrustumPlanes[5].w = ViewProjMatrix[3][3] - ViewProjMatrix[3][2];
	}
}