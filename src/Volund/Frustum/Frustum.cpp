#include "PCH/PCH.h"
#include "Frustum.h"

namespace Volund
{
	bool Frustum::ContainsAABB(const AABB& aabb) const
	{
		VOLUND_PROFILE_FUNCTION();

		Vec4 axisVert(1.0f);

		for (int32_t y = 0; y < 6; y++)
		{
			// x-axis
			if (m_FrustumPlanes[y].x < 0.0f)
			{
				axisVert.x = aabb.Min.x;
			}
			else
			{
				axisVert.x = aabb.Max.x;
			}
			
			// y-axis
			if (m_FrustumPlanes[y].y < 0.0f)
			{
				axisVert.y = aabb.Min.y;
			}
			else
			{
				axisVert.y = aabb.Max.y;
			}

			// z-axis
			if (m_FrustumPlanes[y].z < 0.0f)
			{
				axisVert.z = aabb.Min.z;
			}
			else
			{
				axisVert.z = aabb.Max.z;
			}

			if (Math::Dot(m_FrustumPlanes[y], axisVert) < 0.0f)
			{
				return false;
			}
		}

		return true;
	}

	Frustum::Frustum(Mat4x4 viewProjMatrix)	
	{
		VOLUND_PROFILE_FUNCTION();

		auto test = (viewProjMatrix[0]);

		// Left clipping plane
		m_FrustumPlanes[0].x = viewProjMatrix[0][3] + viewProjMatrix[0][0];
		m_FrustumPlanes[0].y = viewProjMatrix[1][3] + viewProjMatrix[1][0];
		m_FrustumPlanes[0].z = viewProjMatrix[2][3] + viewProjMatrix[2][0];
		m_FrustumPlanes[0].w = viewProjMatrix[3][3] + viewProjMatrix[3][0];
		// Right clipping plane
		m_FrustumPlanes[1].x = viewProjMatrix[0][3] - viewProjMatrix[0][0];
		m_FrustumPlanes[1].y = viewProjMatrix[1][3] - viewProjMatrix[1][0];
		m_FrustumPlanes[1].z = viewProjMatrix[2][3] - viewProjMatrix[2][0];
		m_FrustumPlanes[1].w = viewProjMatrix[3][3] - viewProjMatrix[3][0];
		// Top clipping plane
		m_FrustumPlanes[2].x = viewProjMatrix[0][3] - viewProjMatrix[0][1];
		m_FrustumPlanes[2].y = viewProjMatrix[1][3] - viewProjMatrix[1][1];
		m_FrustumPlanes[2].z = viewProjMatrix[2][3] - viewProjMatrix[2][1];
		m_FrustumPlanes[2].w = viewProjMatrix[3][3] - viewProjMatrix[3][1];
		// Bottom clipping plane
		m_FrustumPlanes[3].x = viewProjMatrix[0][3] + viewProjMatrix[0][1];
		m_FrustumPlanes[3].y = viewProjMatrix[1][3] + viewProjMatrix[1][1];
		m_FrustumPlanes[3].z = viewProjMatrix[2][3] + viewProjMatrix[2][1];
		m_FrustumPlanes[3].w = viewProjMatrix[3][3] + viewProjMatrix[3][1];
		// Near clipping plane
		m_FrustumPlanes[4].x = viewProjMatrix[0][2];
		m_FrustumPlanes[4].y = viewProjMatrix[1][2];
		m_FrustumPlanes[4].z = viewProjMatrix[2][2];
		m_FrustumPlanes[4].w = viewProjMatrix[3][2];
		// Far clipping plane
		m_FrustumPlanes[5].x = viewProjMatrix[0][3] - viewProjMatrix[0][2];
		m_FrustumPlanes[5].y = viewProjMatrix[1][3] - viewProjMatrix[1][2];
		m_FrustumPlanes[5].z = viewProjMatrix[2][3] - viewProjMatrix[2][2];
		m_FrustumPlanes[5].w = viewProjMatrix[3][3] - viewProjMatrix[3][2];

		for (int i = 0; i < 6; i++)
		{
			m_FrustumPlanes[i] = Math::Normalize(m_FrustumPlanes[i]);
		}
	}
}