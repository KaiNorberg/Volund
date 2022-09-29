#include "PCH/PCH.h"

#include "Math.h"

namespace Volund
{
	const Vec3 Math::Up = Vec3(0, 1, 0);

	const Vec3 Math::Down = Vec3(0, -1, 0);

	const Vec3 Math::Forward = Vec3(0, 0, 1);

	const Vec3 Math::Back = Vec3(0, 0, -1);

	const Vec3 Math::Left = Vec3(-1, 0, 0);

	const Vec3 Math::Right = Vec3(1, 0, 0);

	const Vec3 Math::One = Vec3(1, 1, 1);

	const Vec3 Math::Zero = Vec3(0, 0, 0);

	int Math::RoundUp(int N, int M)
	{
		if (M == 0)
		{
			return N;
		}

		int R = N % M;
		if (R == 0)
		{
			return N;
		}

		return N + M - R;
	}
}
