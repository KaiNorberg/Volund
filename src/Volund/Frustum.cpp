#include "Frustum.hpp"

#include "Instrumentor.hpp"

namespace Volund
{
	bool Frustum::ContainsAABB(const AABB& aabb) const
	{
		VOLUND_PROFILE_FUNCTION();

		Vec4 axisVert(1.0f);

		for (int32_t y = 0; y < 6; y++)
		{
			// x-axis
			if (m_frustumPlanes[y].x < 0.0f)
			{
				axisVert.x = aabb.Min.x;
			}
			else
			{
				axisVert.x = aabb.Max.x;
			}

			// y-axis
			if (m_frustumPlanes[y].y < 0.0f)
			{
				axisVert.y = aabb.Min.y;
			}
			else
			{
				axisVert.y = aabb.Max.y;
			}

			// z-axis
			if (m_frustumPlanes[y].z < 0.0f)
			{
				axisVert.z = aabb.Min.z;
			}
			else
			{
				axisVert.z = aabb.Max.z;
			}

			if (Math::Dot(m_frustumPlanes[y], axisVert) < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

	Frustum::Frustum(const Mat4x4& viewProjMatrix)
	{
		VOLUND_PROFILE_FUNCTION();

		auto test = (viewProjMatrix[0]);

		// Left clipping plane
		m_frustumPlanes[0].x = viewProjMatrix[0][3] + viewProjMatrix[0][0];
		m_frustumPlanes[0].y = viewProjMatrix[1][3] + viewProjMatrix[1][0];
		m_frustumPlanes[0].z = viewProjMatrix[2][3] + viewProjMatrix[2][0];
		m_frustumPlanes[0].w = viewProjMatrix[3][3] + viewProjMatrix[3][0];
		// Right clipping plane
		m_frustumPlanes[1].x = viewProjMatrix[0][3] - viewProjMatrix[0][0];
		m_frustumPlanes[1].y = viewProjMatrix[1][3] - viewProjMatrix[1][0];
		m_frustumPlanes[1].z = viewProjMatrix[2][3] - viewProjMatrix[2][0];
		m_frustumPlanes[1].w = viewProjMatrix[3][3] - viewProjMatrix[3][0];
		// Top clipping plane
		m_frustumPlanes[2].x = viewProjMatrix[0][3] - viewProjMatrix[0][1];
		m_frustumPlanes[2].y = viewProjMatrix[1][3] - viewProjMatrix[1][1];
		m_frustumPlanes[2].z = viewProjMatrix[2][3] - viewProjMatrix[2][1];
		m_frustumPlanes[2].w = viewProjMatrix[3][3] - viewProjMatrix[3][1];
		// Bottom clipping plane
		m_frustumPlanes[3].x = viewProjMatrix[0][3] + viewProjMatrix[0][1];
		m_frustumPlanes[3].y = viewProjMatrix[1][3] + viewProjMatrix[1][1];
		m_frustumPlanes[3].z = viewProjMatrix[2][3] + viewProjMatrix[2][1];
		m_frustumPlanes[3].w = viewProjMatrix[3][3] + viewProjMatrix[3][1];
		// Near clipping plane
		m_frustumPlanes[4].x = viewProjMatrix[0][2];
		m_frustumPlanes[4].y = viewProjMatrix[1][2];
		m_frustumPlanes[4].z = viewProjMatrix[2][2];
		m_frustumPlanes[4].w = viewProjMatrix[3][2];
		// Far clipping plane
		m_frustumPlanes[5].x = viewProjMatrix[0][3] - viewProjMatrix[0][2];
		m_frustumPlanes[5].y = viewProjMatrix[1][3] - viewProjMatrix[1][2];
		m_frustumPlanes[5].z = viewProjMatrix[2][3] - viewProjMatrix[2][2];
		m_frustumPlanes[5].w = viewProjMatrix[3][3] - viewProjMatrix[3][2];

		for (int i = 0; i < 6; i++)
		{
			m_frustumPlanes[i] = Math::Normalize(m_frustumPlanes[i]);
		}
	}
}
