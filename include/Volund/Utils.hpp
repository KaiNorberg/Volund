#pragma once

#include "Core.hpp"

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

    bool VOLUND_API CheckBit(uint32_t var, uint8_t pos);

    std::filesystem::path VOLUND_API GenerateUniquePath(const std::filesystem::path& basePath);

    std::filesystem::path VOLUND_API RelativePath(const std::filesystem::path& path, const std::filesystem::path& parentPath);

    std::vector<std::string_view> VOLUND_API SplitString(std::string_view string, const char delimiter);

    int VOLUND_API Svtoi(std::string_view string);

    float VOLUND_API Svtof(std::string_view string);

    uint32_t VOLUND_API CastFloatToInt(float value);

    float VOLUND_API CastIntToFloat(int value);

    int VOLUND_API RoundUp(int n, int m);
}
