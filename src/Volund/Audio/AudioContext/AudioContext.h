#pragma once

#include "Audio/AudioDevice/AudioDevice.h"

struct ALCcontext;

namespace Volund
{
    class AudioContext
    {
    public:

        ALCcontext* GetContext() const;

        void MakeCurrent();

        AudioContext(const AudioDevice& device);

        AudioContext(Ref<AudioDevice> device);

        ~AudioContext();

    private:

        ALCdevice* m_Device;
        ALCcontext* m_Context;
    };
}