#pragma once

namespace Volund
{
    class ImageLoader
    {
    public:

        int32_t GetWidth() const;

        int32_t GetHeight() const;

        int32_t GetChannels() const;

        unsigned char* GetData() const;

        void Load(const std::string& filepath, bool flip = true, int32_t desiredChannels = 4);

        ImageLoader() = default;

        ImageLoader(const std::string& filepath, bool flip = true, int32_t desiredChannels = 4);

        ~ImageLoader();

    private:

        int32_t m_Width = 0;

        int32_t m_Height = 0;

        int32_t m_Channels = 0;

        unsigned char* m_Data = nullptr;
    };
}
