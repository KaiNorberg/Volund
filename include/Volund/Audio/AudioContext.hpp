#pragma once

#include "AudioDevice.hpp"

#include <memory>

#include <AL/al.h>
#include <AL/alext.h>

struct ALCcontext;

namespace Volund
{
    class VOLUND_API AudioContext
    {
    public:
        ALCcontext* GetContext() const;
        void MakeCurrent();
        AudioContext(const AudioDevice& device);
        AudioContext(std::shared_ptr<AudioDevice> device);
        ~AudioContext();
    private:
        ALCdevice* m_device;
        ALCcontext* m_context;
    };
}