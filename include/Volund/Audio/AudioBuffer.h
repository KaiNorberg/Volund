#pragma once

#include <cstdint>
#include <string>

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
    class AudioBuffer
    {
    public:
        std::string GetFilepath();
        uint32_t GetBuffer() const;
        AudioBuffer(std::string const& filepath);
        ~AudioBuffer();
    private:
        std::string m_filepath;
        uint32_t m_buffer = 0;
    };
}
