#pragma once

#define PI 3.14159265359f

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

	bool CheckBit(uint32_t var, uint8_t pos);

	fs::path GenerateUniquePath(const fs::path& basePath);

	fs::path RelativePath(const fs::path& path, const fs::path& parentPath);

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