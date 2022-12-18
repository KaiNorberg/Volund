#include "PCH/PCH.h"
#include "AABB.h"

#include <glm/glm/gtx/matrix_decompose.hpp>

namespace Volund
{
	AABB AABB::ToWorldSpace(const Mat4x4& ModelMatrix)
	{
		glm::vec3 Scale;
		glm::quat Rotation;
		glm::vec3 Position;
		glm::vec3 Skew;
		glm::vec4 Perspective;
		glm::decompose(ModelMatrix, Scale, Rotation, Position, Skew, Perspective);

		AABB NewAABB = AABB(Position, Position);
		glm::mat3x3 RotationMatrix = glm::toMat3(Rotation);
		for (int i = 0; i < RotationMatrix.length(); i++)
		{
			for (int j = 0; j < RotationMatrix[i].length(); j++)
			{
				float A = RotationMatrix[i][j] * this->Min[j] * Scale[j];
				float B = RotationMatrix[i][j] * this->Max[j] * Scale[j];
				NewAABB.Min[i] += A < B ? A : B;
				NewAABB.Max[i] += A < B ? B : A;
			}
		}

		return NewAABB;
	}

	AABB::AABB(const std::vector<float>& Points)
	{
		for (uint64_t i = 0; i < Points.size(); i += 3)
		{
			this->Min.x = Utils::Min(this->Min.x, Points[i]);
			this->Max.x = Utils::Max(this->Max.x, Points[i]);

			this->Min.y = Utils::Min(this->Min.y, Points[i + 1]);
			this->Max.y = Utils::Max(this->Max.y, Points[i + 1]);

			this->Min.z = Utils::Min(this->Min.z, Points[i + 2]);
			this->Max.z = Utils::Max(this->Max.z, Points[i + 2]);
		}
	}

	AABB::AABB(const std::vector<Vec3>& Points)
	{
		for (uint64_t i = 0; i < Points.size(); i++)
		{
			this->Min.x = Utils::Min(this->Min.x, Points[i].x);
			this->Max.x = Utils::Max(this->Max.x, Points[i].x);

			this->Min.y = Utils::Min(this->Min.y, Points[i].y);
			this->Max.y = Utils::Max(this->Max.y, Points[i].y);

			this->Min.z = Utils::Min(this->Min.z, Points[i].z);
			this->Max.z = Utils::Max(this->Max.z, Points[i].z);
		}
	}

	AABB::AABB(Vec3 Min, Vec3 Max)
	{
		this->Min = Min;
		this->Max = Max;
	}
}