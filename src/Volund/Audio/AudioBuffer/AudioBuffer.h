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
        uint32_t GetBuffer() const;

        AudioBuffer(std::string const& filepath);
        ~AudioBuffer();
    private:
        uint32_t m_buffer = 0;
    };
}
