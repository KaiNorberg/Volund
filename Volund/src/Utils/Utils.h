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
	static inline const Vec3 UP = Vec3(0, 1, 0);
	static inline const Vec3 DOWN = Vec3(0, -1, 0);
	static inline const Vec3 FORWARD = Vec3(0, 0, 1);
	static inline const Vec3 BACK = Vec3(0, 0, -1);
	static inline const Vec3 LEFT = Vec3(-1, 0, 0);
	static inline const Vec3 RIGHT = Vec3(1, 0, 0);
	static inline const Vec3 ONE = Vec3(1, 1, 1);
	static inline const Vec3 ZERO = Vec3(0, 0, 0);

	std::vector<std::string_view> SplitString(std::string_view string, const char delimiter);

	int Svtoi(std::string_view string);

	float Svtof(std::string_view string);

	uint32_t CastFloatToInt(float value);

	float CastIntToFloat(int value);

	int RoundUp(int n, int m);

	/*template <class T>
	T ToRadians(const T& v)
	{
		return (PI / 180.0f) * v;
	}

	template <class T>
	T ToDegrees(const T& v)
	{
		return (180.0f / PI) * v;
	}

	template <class T>
	T Min(T n1, T n2)
	{
		return (n1 < n2) ? n1 : n2;
	}

	template <class T>
	T Max(T n1, T n2)
	{
		return (n1 > n2) ? n1 : n2;
	}

	template <class T>
	T Clamp(T n, T lower, T upper)
	{
		return Max(lower, Min(n, upper));
	}*/
}