#pragma once

//#include "Vec/Vec2.h"
//#include "Vec/Vec3.h"
//#include "Vec/Vec4.h"
//#include "Mat/Mat4x4.h"

#define PI 3.14159265359f

namespace Volund
{		
	class Math
	{
	public:
		/// <summary>
		/// A vector pointing up.
		/// </summary>
		static const Vec3 Up;

		/// <summary>
		/// A vector pointing down.
		/// </summary>
		static const Vec3 Down;

		/// <summary>
		/// A vector pointing Forward.
		/// </summary>
		static const Vec3 Forward;

		/// <summary>
		/// A vector pointing Backward.
		/// </summary>
		static const Vec3 Back;

		/// <summary>
		/// A vector pointing Left.
		/// </summary>
		static const Vec3 Left;

		/// <summary>
		/// A vector pointing Right.
		/// </summary>
		static const Vec3 Right;

		/// <summary>
		/// A vector filled with ones.
		/// </summary>
		static const Vec3 One;

		/// <summary>
		/// A vector filled with zeros.
		/// </summary>
		static const Vec3 Zero;

		static Vec3 Euler(Quat const& Q);

		template <class T>
		static T ToRadians(T const& V)
		{
			return (PI / 180.0f) * V;
		}

		template <class T>
		static T ToDegrees(T const& V)
		{
			return (180.0f / PI) * V;
		}

		template <class T>
		static T Min(T N1, T N2)
		{
			return (N1 < N2) ? N1 : N2;
		}

		template <class T>
		static T Max(T N1, T N2)
		{
			return (N1 > N2) ? N1 : N2;
		}		
		
		template <class T>
		static T Clamp(T N, T Lower, T Upper) 
		{
			return Max(Lower, Min(N, Upper));
		}
	private:
	};
}