#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
    class AudioSource
    {
    public:

        void Play();

        void SetBuffer(std::shared_ptr<AudioBuffer> buffer);
        std::shared_ptr<AudioBuffer> GetBuffer();

        void SetPosition(const Vec3& position);

        void SetDirection(const Vec3& direction);

        void SetVelocity(const Vec3& velocity);

        void SetPitch(float pitch);
        float GetPitch();

        void SetLooping(bool looping);
        bool GetLooping();

        void SetGain(float gain);
        float GetGain();

        AudioSource();

        ~AudioSource();

    private:

        std::shared_ptr<AudioBuffer> m_Buffer;

        uint32_t m_Source;
    };
}
