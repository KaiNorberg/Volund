#pragma once

#include "Vec/Vec2.h"
#include "Vec/Vec3.h"
#include "Vec/Vec4.h"
#include "Mat/Mat4x4.h"

namespace Volund
{
	template <class T>
	T Min(T N1, T N2)
	{
		return (N1 < N2) ? N1 : N2;
	}

	template <class T>
	T Max(T N1, T N2)
	{
		return (N1 > N2) ? N1 : N2;
	}
}