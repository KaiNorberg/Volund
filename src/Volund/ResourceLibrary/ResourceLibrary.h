#pragma once

namespace Volund
{
    class ResourceLibrary
    {
    public:

        static bool IsResource(const std::string& filepath);

        static const char* Fetch(const std::string& filepath);

        static const std::unordered_map<std::string, const char*>& Map();

    private:

        ResourceLibrary();

        static void CreateResource(const std::string& filepath, const char* content);

        static inline std::unordered_map<std::string, const char*> m_Resources;
    };
}