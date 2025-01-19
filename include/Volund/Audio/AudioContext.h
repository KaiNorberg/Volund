#pragma once

#include "AudioDevice.h"

#include <memory>

#include <AL/al.h>
#include <AL/alext.h>

struct ALCcontext;

namespace Volund
{
    class AudioContext
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