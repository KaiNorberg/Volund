#pragma once

#include <vector>
#include <string_view>
#include <filesystem>

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

    std::filesystem::path GenerateUniquePath(const std::filesystem::path& basePath);

    std::filesystem::path RelativePath(const std::filesystem::path& path, const std::filesystem::path& parentPath);

    std::vector<std::string_view> SplitString(std::string_view string, const char delimiter);

    int Svtoi(std::string_view string);

    float Svtof(std::string_view string);

    uint32_t CastFloatToInt(float value);

    float CastIntToFloat(int value);

    int RoundUp(int n, int m);
}
