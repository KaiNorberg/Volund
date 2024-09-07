#pragma once

#include "Math/Math.h"

namespace Volund::Utils
{
    //TODO: this sucks, make it better
    template<typename T>
    inline uint64_t GetTypeId()
    {
        static const uint64_t typeId = typeid(T).hash_code();
        return typeId;
    }

    bool CheckBit(uint32_t var, uint8_t pos);

    fs::path GenerateUniquePath(const fs::path& basePath);

    fs::path RelativePath(const fs::path& path, const fs::path& parentPath);

    std::vector<std::string_view> SplitString(std::string_view string, const char delimiter);

    int Svtoi(std::string_view string);

    float Svtof(std::string_view string);

    uint32_t CastFloatToInt(float value);

    float CastIntToFloat(int value);

    int RoundUp(int n, int m);
}