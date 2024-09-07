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

        void SetBuffer(Ref<AudioBuffer> buffer);
        
        Ref<AudioBuffer> GetBuffer();

        void SetPitch(float pitch);
        float GetPitch();

        void SetLooping(bool looping);
        bool GetLooping();

        void SetGain(float gain);
        float GetGain();

        void Procedure(const Event& e);

        SoundSource() = default;

    private:

        bool m_HasAutoPlayed = false;

        AudioSource m_Source;
    };
}
