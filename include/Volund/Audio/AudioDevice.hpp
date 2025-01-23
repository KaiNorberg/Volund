#pragma once

#include "../Core.hpp"

#include <AL/al.h>
#include <AL/alext.h>

#include <string>

struct ALCdevice;

namespace Volund
{
    class VOLUND_API AudioDevice
    {
    public:
        ALCdevice* GetDevice() const;
        AudioDevice(std::string const& device);
        ~AudioDevice();
    private:
        ALCdevice* m_device;
    };
}
