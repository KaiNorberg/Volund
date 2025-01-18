#pragma once

#include "../Component.h"

#include "Audio/AudioSource/AudioSource.h"

namespace Volund
{
    class SoundSource : public Component
    {
    public:

        bool AutoPlay = false;

        void Play();

        void SetBuffer(std::shared_ptr<AudioBuffer> buffer);

        std::shared_ptr<AudioBuffer> GetBuffer();

        void SetPitch(float pitch);
        float GetPitch();

        void SetLooping(bool looping);
        bool GetLooping();

        void SetGain(float gain);
        float GetGain();

        void Procedure(const Event& e);

        SoundSource(std::shared_ptr<AudioBuffer> buffer = nullptr);

    private:

        bool m_hasAutoPlayed = false;

        AudioSource m_source;
    };
}
