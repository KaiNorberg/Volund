#pragma once

namespace Volund
{
	class AABB
	{
	public:

		Vec3 Min;

		Vec3 Max;

		AABB ToWorldSpace(const Mat4x4& ModelMatrix);

		AABB() = default;

		AABB(const std::vector<float>& Points);

		AABB(const std::vector<Vec3>& Points);

		AABB(Vec3 Min, Vec3 Max);

	private:
	};
}

