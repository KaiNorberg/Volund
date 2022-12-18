#include "PCH/PCH.h"
#include "AABB.h"

namespace Volund
{
	AABB AABB::ToWorldSpace(const Mat4x4& ModelMatrix)
	{
		std::array<Vec3, 8> Points;

		Points[0] = (Vec3(Vec4(this->Min.x, this->Min.y, this->Min.z, 1.0)* ModelMatrix));
		Points[1] = (Vec3(Vec4(this->Max.x, this->Min.y, this->Min.z, 1.0) * ModelMatrix));
		Points[2] = (Vec3(Vec4(this->Min.x, this->Max.y, this->Min.z, 1.0) * ModelMatrix));
		Points[3] = (Vec3(Vec4(this->Max.x, this->Max.y, this->Min.z, 1.0) * ModelMatrix));
		Points[4] = (Vec3(Vec4(this->Min.x, this->Min.y, this->Max.z, 1.0) * ModelMatrix));
		Points[5] = (Vec3(Vec4(this->Max.x, this->Min.y, this->Max.z, 1.0) * ModelMatrix));
		Points[6] = (Vec3(Vec4(this->Min.x, this->Max.y, this->Max.z, 1.0) * ModelMatrix));
		Points[7] = (Vec3(Vec4(this->Max.x, this->Max.y, this->Max.z, 1.0) * ModelMatrix));

		AABB NewAABB;

		for (uint64_t i = 0; i < Points.size(); i++)
		{
			NewAABB.Min.x = Utils::Min(NewAABB.Min.x, Points[i].x);
			NewAABB.Max.x = Utils::Max(NewAABB.Max.x, Points[i].x);

			NewAABB.Min.y = Utils::Min(NewAABB.Min.y, Points[i].y);
			NewAABB.Max.y = Utils::Max(NewAABB.Max.y, Points[i].y);

			NewAABB.Min.z = Utils::Min(NewAABB.Min.z, Points[i].z);
			NewAABB.Max.z = Utils::Max(NewAABB.Max.z, Points[i].z);
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