#pragma once

namespace Volund
{
	class AABB
	{
	public:

		Vec3 Min;

		Vec3 Max;

		AABB() = default;

		AABB(Vec3 Min, Vec3 Max);

	private:
	};
}

