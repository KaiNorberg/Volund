#include "PCH/PCH.h"
#include "AABB.h"

namespace Volund
{
	AABB AABB::ToWorldSpace(const Mat4x4& modelMatrix)
	{
		/*VOLUND_PROFILE_FUNCTION();

		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 position;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(modelMatrix, scale, rotation, position, skew, perspective);

		AABB newAABB = AABB(position, position);
		glm::mat3x3 rotationMatrix = glm::toMat3(rotation);
		for (int i = 0; i < rotationMatrix.length(); i++)
		{
			for (int j = 0; j < rotationMatrix[i].length(); j++)
			{
				float a = rotationMatrix[i][j] * this->Min[j] * scale[j];
				float b = rotationMatrix[i][j] * this->Max[j] * scale[j];
				newAABB.Min[i] += a < b ? a : b;
				newAABB.Max[i] += a < b ? b : a;
			}
		}

		return newAABB;*/
		return AABB();
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