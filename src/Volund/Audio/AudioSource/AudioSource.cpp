#include "PCH/PCH.h"
#include "AudioSource.h"

#include "Audio/Audio.h"

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
    void AudioSource::Play()
    {
        AL_CALL(alSourcePlay, this->m_Source);
    }

    void AudioSource::SetBuffer(const Ref<AudioBuffer> buffer)
    {
        this->m_Buffer = buffer;
        AL_CALL(alSourcei, this->m_Source, AL_BUFFER, buffer->GetBuffer());
    }

    Ref<AudioBuffer> AudioSource::GetBuffer()
    {
        return this->m_Buffer;
    }

    void AudioSource::SetPosition(const Vec3& position)
    {
        AL_CALL(alSource3f, this->m_Source, AL_POSITION,
            position.x, position.y, position.z);
    }

    void AudioSource::SetDirection(const Vec3& direction)
    {
        AL_CALL(alSource3f, this->m_Source, AL_DIRECTION,
            direction.x, direction.y, direction.z);
    }

    void AudioSource::SetVelocity(const Vec3& velocity)
    {
        AL_CALL(alSource3f, this->m_Source, AL_VELOCITY,
            velocity.x, velocity.y, velocity.z);
    }

    void AudioSource::SetPitch(const float pitch)
    {
        AL_CALL(alSourcef, this->m_Source, AL_PITCH, pitch);
    }

    float AudioSource::GetPitch()
    {
        float out;
        AL_CALL(alGetSourcef, this->m_Source, AL_PITCH, &out);
        return out;
    }

    void AudioSource::SetLooping(const bool looping)
    {
        AL_CALL(alSourcei, this->m_Source, AL_LOOPING, looping);
    }

    bool AudioSource::GetLooping()
    {
        int out;
        AL_CALL(alGetSourcei, this->m_Source, AL_LOOPING, &out);
        return out;
    }

    void AudioSource::SetGain(const float gain)
    {
        AL_CALL(alSourcef, this->m_Source, AL_GAIN, gain);
    }

    float AudioSource::GetGain()
    {
        float out;
        AL_CALL(alGetSourcef, this->m_Source, AL_GAIN, &out);
        return out;
    }

    AudioSource::AudioSource()
	{
        AL_CALL(alGenSources, 1, &this->m_Source);
        AL_CALL(alSourcef, this->m_Source, AL_PITCH, 1);
        AL_CALL(alSourcef, this->m_Source, AL_GAIN, 1.0f);
        AL_CALL(alSource3f, this->m_Source, AL_POSITION, 0, 0, 0);
        AL_CALL(alSource3f, this->m_Source, AL_VELOCITY, 0, 0, 0);
        AL_CALL(alSourcei, this->m_Source, AL_LOOPING, AL_FALSE);
	}

    AudioSource::~AudioSource()
    {
        AL_CALL(alSourceStop, this->m_Source);
        AL_CALL(alDeleteSources, 1, &this->m_Source);
    }
}
