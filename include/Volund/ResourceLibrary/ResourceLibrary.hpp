#pragma once

#include "../Core.hpp"

#include <string>
#include <unordered_map>

namespace Volund
{
    class VOLUND_API ResourceLibrary
    {
    public:
        static bool IsResource(std::string const& filepath);
        static const char* Fetch(std::string const& filepath);
        static const std::unordered_map<std::string, const char*>& Map();
    private:
        ResourceLibrary();
        static void CreateResource(std::string const& filepath, const char* content);
        static inline std::unordered_map<std::string, const char*> m_resources;
    };
}
