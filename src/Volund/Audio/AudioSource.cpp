#include "Audio/AudioSource.hpp"

#include "Audio/Audio.hpp"

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
    void AudioSource::Play()
    {
        AL_CALL(alSourcePlay, this->m_source);
    }

    void AudioSource::SetBuffer(const std::shared_ptr<AudioBuffer> buffer)
    {
        this->m_buffer = buffer;
        AL_CALL(alSourcei, this->m_source, AL_BUFFER, buffer->GetBuffer());
    }

    std::shared_ptr<AudioBuffer> AudioSource::GetBuffer()
    {
        return this->m_buffer;
    }

    void AudioSource::SetPosition(const Vec3& position)
    {
        AL_CALL(alSource3f, this->m_source, AL_POSITION,
            position.x, position.y, position.z);
    }

    void AudioSource::SetDirection(const Vec3& direction)
    {
        AL_CALL(alSource3f, this->m_source, AL_DIRECTION,
            direction.x, direction.y, direction.z);
    }

    void AudioSource::SetVelocity(const Vec3& velocity)
    {
        AL_CALL(alSource3f, this->m_source, AL_VELOCITY,
            velocity.x, velocity.y, velocity.z);
    }

    void AudioSource::SetPitch(const float pitch)
    {
        AL_CALL(alSourcef, this->m_source, AL_PITCH, pitch);
    }

    float AudioSource::GetPitch()
    {
        float out;
        AL_CALL(alGetSourcef, this->m_source, AL_PITCH, &out);
        return out;
    }

    void AudioSource::SetLooping(const bool looping)
    {
        AL_CALL(alSourcei, this->m_source, AL_LOOPING, looping);
    }

    bool AudioSource::GetLooping()
    {
        int out;
        AL_CALL(alGetSourcei, this->m_source, AL_LOOPING, &out);
        return out;
    }

    void AudioSource::SetGain(const float gain)
    {
        AL_CALL(alSourcef, this->m_source, AL_GAIN, gain);
    }

    float AudioSource::GetGain()
    {
        float out;
        AL_CALL(alGetSourcef, this->m_source, AL_GAIN, &out);
        return out;
    }

    AudioSource::AudioSource()
	{
        AL_CALL(alGenSources, 1, &this->m_source);
        AL_CALL(alSourcef, this->m_source, AL_PITCH, 1);
        AL_CALL(alSourcef, this->m_source, AL_GAIN, 1.0f);
        AL_CALL(alSource3f, this->m_source, AL_POSITION, 0, 0, 0);
        AL_CALL(alSource3f, this->m_source, AL_VELOCITY, 0, 0, 0);
        AL_CALL(alSourcei, this->m_source, AL_LOOPING, AL_FALSE);
	}

    AudioSource::~AudioSource()
    {
        AL_CALL(alSourceStop, this->m_source);
        AL_CALL(alDeleteSources, 1, &this->m_source);
    }
}