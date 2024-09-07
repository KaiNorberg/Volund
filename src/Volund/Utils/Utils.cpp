#include "PCH/PCH.h"

#include "Utils.h"

namespace Volund::Utils
{
	bool CheckBit(uint32_t var, uint8_t pos)
	{
		return ((var) & (1 << (pos)));
	}

	fs::path GenerateUniquePath(const fs::path& basePath)
	{
		fs::path filepath = basePath;
		if (fs::exists(filepath))
		{
			int i = 2;
			while (true)
			{
				std::string basePathString = basePath.string();

				uint64_t splitPoint = basePathString.find_first_of(".");
				std::string pathNoExtension = basePathString.substr(0, splitPoint);
				std::string pathExtension = basePathString.substr(splitPoint);

				filepath = fs::path(pathNoExtension + " (" + std::to_string(i) + ")" + pathExtension);
				if (!fs::exists(filepath))
				{
					return filepath;
				}
				i++;
			}
		}
		else
		{
			return filepath;
		}
	}

	fs::path RelativePath(const fs::path& path, const fs::path& parentPath)
	{
		fs::path relativePath = fs::relative(path.parent_path(), parentPath);
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