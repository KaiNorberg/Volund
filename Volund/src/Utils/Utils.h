#pragma once

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
}

namespace Volund::Utils
{
	static inline const Vec3 Up = Vec3(0, 1, 0);
	static inline const Vec3 Down = Vec3(0, -1, 0);
	static inline const Vec3 Forward = Vec3(0, 0, 1);
	static inline const Vec3 Back = Vec3(0, 0, -1);
	static inline const Vec3 Left = Vec3(-1, 0, 0);
	static inline const Vec3 Right = Vec3(1, 0, 0);
	static inline const Vec3 One = Vec3(1, 1, 1);
	static inline const Vec3 Zero = Vec3(0, 0, 0);

    std::string ReplaceAll(std::string Str, const std::string& From, const std::string& To);

    std::wstring ConvertToWString(std::string_view String);		

	int RoundUp(int N, int M);

	template <class T>
	T ToRadians(const T& V)
	{
		return (PI / 180.0f) * V;
	}

	template <class T>
	T ToDegrees(const T& V)
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

	template <class T>
	T Clamp(T N, T Lower, T Upper)
	{
		return Max(Lower, Min(N, Upper));
	}
}