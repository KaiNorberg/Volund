#include "PCH/PCH.h"

#include "Utils.h"

namespace Volund::Utils
{
	uint32_t CastFloatToInt(float Value)
	{
		union { float f; int i; } u;
		u.f = Value;
		return u.i;
	}

	float CastIntToFloat(int Value)
	{
		union { float f; int i; } u;
		u.i = Value;
		return u.f;
	}

    std::string ReplaceAll(std::string Str, const std::string& From, const std::string& To) 
    {
        size_t start_pos = 0;

        while ((start_pos = Str.find(From, start_pos)) != std::string::npos) 
        {
            Str.replace(start_pos, From.length(), To);
            start_pos += To.length();
        }

        return Str;
    }

    std::wstring ConvertToWString(std::string_view String)
    {
        return std::wstring(String.begin(), String.end());
    }	

	int RoundUp(int N, int M)
	{
		if (M == 0)
		{
			return N;
		}

		int R = N % M;
		if (R == 0)
		{
			return N;
		}

		return N + M - R;
	}
}