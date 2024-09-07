#include "PCH/PCH.h"
#include "AABB.h"

namespace Volund
{
	AABB AABB::ToWorldSpace(const Mat4x4& modelMatrix)
	{
		VOLUND_PROFILE_FUNCTION();

		Vec3 position = modelMatrix * Vec3(0.0f);

		AABB newAABB = AABB(position, position);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				float a = modelMatrix[i][j] * this->Min[j];
				float b = modelMatrix[i][j] * this->Max[j];
				newAABB.Min[i] += a < b ? a : b;
				newAABB.Max[i] += a < b ? b : a;
			}
		}

		return newAABB;
	}

	AABB::AABB(const float points[], const uint32_t count)
	{
		for (uint64_t i = 0; i < count; i += 3)
		{
			this->Min.x = std::min(this->Min.x, points[i]);
			this->Max.x = std::max(this->Max.x, points[i]);

			this->Min.y = std::min(this->Min.y, points[i + 1]);
			this->Max.y = std::max(this->Max.y, points[i + 1]);

			this->Min.z = std::min(this->Min.z, points[i + 2]);
			this->Max.z = std::max(this->Max.z, points[i + 2]);
		}
	}

	AABB::AABB(const std::vector<float>& points)
	{
		for (uint64_t i = 0; i < points.size(); i += 3)
		{
			this->Min.x = std::min(this->Min.x, points[i]);
			this->Max.x = std::max(this->Max.x, points[i]);

			this->Min.y = std::min(this->Min.y, points[i + 1]);
			this->Max.y = std::max(this->Max.y, points[i + 1]);

			this->Min.z = std::min(this->Min.z, points[i + 2]);
			this->Max.z = std::max(this->Max.z, points[i + 2]);
		}
	}

	AABB::AABB(const std::vector<Vec3>& points)
	{
		for (uint64_t i = 0; i < points.size(); i++)
		{
			this->Min.x = std::min(this->Min.x, points[i].x);
			this->Max.x = std::max(this->Max.x, points[i].x);

			this->Min.y = std::min(this->Min.y, points[i].y);
			this->Max.y = std::max(this->Max.y, points[i].y);

			this->Min.z = std::min(this->Min.z, points[i].z);
			this->Max.z = std::max(this->Max.z, points[i].z);
		}
	}

	AABB::AABB(const Vec3 min, const Vec3 max)
	{
		this->Min = min;
		this->Max = max;
	}
}