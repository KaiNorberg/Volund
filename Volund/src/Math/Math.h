#pragma once

//#include "Vec/Vec2.h"
//#include "Vec/Vec3.h"
//#include "Vec/Vec4.h"
//#include "Mat/Mat4x4.h"

#define PI 3.14159265359f

namespace Volund::Math
{		
	/// <summary>
	/// A vector pointing up.
	/// </summary>
	static const Vec3 Up = Vec3(0, 1, 0);

	/// <summary>
	/// A vector pointing down.
	/// </summary>
	static const Vec3 Down = Vec3(0, -1, 0);

	/// <summary>
	/// A vector pointing Forward.
	/// </summary>
	static const Vec3 Forward = Vec3(0, 0, 1);

	/// <summary>
	/// A vector pointing Backward.
	/// </summary>
	static const Vec3 Back = Vec3(0, 0, -1);

	/// <summary>
	/// A vector pointing Left.
	/// </summary>
	static const Vec3 Left = Vec3(-1, 0, 0);

	/// <summary>
	/// A vector pointing Right.
	/// </summary>
	static const Vec3 Right = Vec3(1, 0, 0);

	/// <summary>
	/// A vector filled with ones.
	/// </summary>
	static const Vec3 One = Vec3(1, 1, 1);

	/// <summary>
	/// A vector filled with zeros.
	/// </summary>
	static const Vec3 Zero = Vec3(0, 0, 0);

	Vec3 Euler(Quat const& Q);

	template <class T>
	T ToRadians(T const& V)
	{
		return (PI / 180.0f) * V;
	}

	template <class T>
	T ToDegrees(T const& V)
	{
		return (180.0f / PI) * V;
	}

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