#pragma once

#include <cstdint>
#include <string>

namespace Volund
{
    class ImageLoader
    {
    public:
        int32_t GetWidth() const;
        int32_t GetHeight() const;
        int32_t GetChannels() const;
        unsigned char* GetData() const;
        void Load(std::string const& filepath);
        ImageLoader() = default;
        ImageLoader(std::string const& filepath, bool flip = true);
        ~ImageLoader();
    private:
        int32_t m_width = 0;
        int32_t m_height = 0;
        int32_t m_channels = 0;
        unsigned char* m_data = nullptr;
        bool m_flip = true;
    };
}
