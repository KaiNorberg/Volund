#include "PCH/PCH.h"

#include "Utils.h"

namespace Volund::Utils
{
	std::filesystem::path RelativePath(const std::filesystem::path& path, const std::filesystem::path& parentPath)
	{
		std::filesystem::path relativePath = std::filesystem::relative(path.parent_path(), parentPath);
		relativePath /= path.filename();
		return relativePath.string();
	}

	std::vector<std::string_view> SplitString(std::string_view string, const char delimiter)
	{
		std::vector<std::string_view> output;
		output.reserve(std::count(string.begin(), string.end(), delimiter) + 1);

		for (auto it = string.begin();; ++it)
		{
			auto newIt = std::find(it, string.end(), delimiter);
			output.emplace_back(it, newIt);
			it = newIt;
			if (it == string.end())
			{
				return output;
			}
		}
	}

	int Svtoi(std::string_view string)
	{
		int output;
		const std::from_chars_result result = std::from_chars(string.data(), string.data() + string.size(), output);
		if (result.ec == std::errc::invalid_argument || result.ec == std::errc::result_out_of_range)
		{
			return 0;
		}
		return output;
	}

	float Svtof(std::string_view string)
	{
		float output;
		const std::from_chars_result result = std::from_chars(string.data(), string.data() + string.size(), output);
		if (result.ec == std::errc::invalid_argument || result.ec == std::errc::result_out_of_range)
		{
			return 0.0f;
		}
		return output;
	}

	uint32_t CastFloatToInt(const float value) 
	{
		union { float f; int i; } u;
		u.f = value;
		return u.i;
	}

	float CastIntToFloat(const int value)
	{
		union { float f; int i; } u;
		u.i = value;
		return u.f;
	}

	int RoundUp(const int n, const int m)
	{
		if (m == 0)
		{
			return n;
		}

		int r = n % m;
		if (r == 0)
		{
			return n;
		}

		return n + m - r;
	}
}