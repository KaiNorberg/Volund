#include "PCH/PCH.h"

#include "Utils.h"

namespace Volund::Utils
{
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

    std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) 
    {
        size_t startPos = 0;

        while ((startPos = str.find(from, startPos)) != std::string::npos) 
        {
            str.replace(startPos, from.length(), to);
            startPos += to.length();
        }

        return str;
    }

    std::wstring ConvertToWString(std::string_view string)
    {
        return std::wstring(string.begin(), string.end());
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