#pragma once

#include <glm/glm/glm.hpp>
#include <glm/glm/vec2.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/quaternion.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#define PI 3.14159265359f

namespace Volund
{
	using Vec2 = glm::vec<2, float>;
	using DVec2 = glm::vec<2, double>;
	using IVec2 = glm::vec<2, int32_t>;
	using I64Vec2 = glm::vec<2, int64_t>;

	using Vec3 = glm::vec<3, float>;
	using DVec3 = glm::vec<3, double>;
	using IVec3 = glm::vec<3, int32_t>;
	using I64Vec3 = glm::vec<3, int64_t>;
	using RGB = Vec3;

	using Vec4 = glm::vec<4, float>;
	using DVec4 = glm::vec<4, double>;
	using IVec4 = glm::vec<4, int32_t>;
	using I64Vec4 = glm::vec<4, int64_t>;
	using RGBA = Vec4;

	using Mat3x3 = glm::mat<3, 3, float>;
	using DMat3x3 = glm::mat<3, 3, double>;
	using IMat3x3 = glm::mat<3, 3, int32_t>;
	using I64Mat3x3 = glm::mat<3, 3, int64_t>;

	using Mat4x4 = glm::mat<4, 4, float>;
	using DMat4x4 = glm::mat<4, 4, double>;
	using IMat4x4 = glm::mat<4, 4, int32_t>;
	using I64Mat4x4 = glm::mat<4, 4, int64_t>;

	using Quat = glm::qua<float>;
	using DQuat = glm::qua<double>;

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

		template <class T>
		static T ToRadians(const T& V)
		{
			return (PI / 180.0f) * V;
		}

		template <class T>
		static T ToDegrees(const T& V)
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

		static int RoundUp(int N, int M);

	private:
	};
}
