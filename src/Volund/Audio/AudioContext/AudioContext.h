#pragma once

#include "Audio/AudioDevice/AudioDevice.h"

#include <memory.h>

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

        ALCdevice* m_Device;
        ALCcontext* m_Context;
    };
}
