#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
    class AudioListener
    {
    public:

        void SetPosition(const Vec3& position);

        void SetOrientation(const Vec3& front, const Vec3& up);

        void SetVelocity(const Vec3& velocity);

        AudioListener();

        ~AudioListener();

    private:
        
        static inline uint32_t m_AudioListenerCount = 0;
    };
}