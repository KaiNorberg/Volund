#include "PCH/PCH.h"
#include "AudioSource.h"

#include "Audio/Audio.h"

namespace Volund
{
    void AudioSource::Play()
    {
        alCall(alSourcePlay, this->_Source);
    }

    void AudioSource::SetBuffer(const AudioBuffer& Buffer)
    {
        alCall(alSourcei, this->_Source, AL_BUFFER, Buffer.GetBuffer());
    }

    void AudioSource::SetBuffer(Ref<AudioBuffer> Buffer)
    {
        alCall(alSourcei, this->_Source, AL_BUFFER, Buffer->GetBuffer());
    }

    void AudioSource::SetPitch(float Pitch)
    {
        alCall(alSourcef, this->_Source, AL_PITCH, Pitch);
    }

    void AudioSource::SetPosition(const Vec3& Position)
    {
        alCall(alSource3f, this->_Source, AL_POSITION,
            Position.x, Position.y, Position.z);
    }

    void AudioSource::SetDirection(const Vec3& Direction)
    {
        alCall(alSource3f, this->_Source, AL_DIRECTION,
            Direction.x, Direction.y, Direction.z);
    }

    void AudioSource::SetVelocity(const Vec3& Velocity)
    {
        alCall(alSource3f, this->_Source, AL_VELOCITY, 
            Velocity.x, Velocity.y, Velocity.z);
    }

    void AudioSource::SetLooping(bool Looping)
    {
        alCall(alSourcei, this->_Source, AL_LOOPING, Looping);
    }

    void AudioSource::SetGain(float Gain)
    {
        alCall(alSourcef, this->_Source, AL_GAIN, Gain);
    }

    AudioSource::AudioSource()
	{
        alCall(alGenSources, 1, &this->_Source);
        alCall(alSourcef, this->_Source, AL_PITCH, 1);
        alCall(alSourcef, this->_Source, AL_GAIN, 1.0f);
        alCall(alSource3f, this->_Source, AL_POSITION, 0, 0, 0);
        alCall(alSource3f, this->_Source, AL_VELOCITY, 0, 0, 0);
        alCall(alSourcei, this->_Source, AL_LOOPING, AL_FALSE);
	}

    AudioSource::~AudioSource()
    {
        alCall(alDeleteSources, 1, &this->_Source);
    }
}