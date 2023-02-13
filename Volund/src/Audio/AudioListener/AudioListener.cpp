#include "PCH/PCH.h"
#include "AudioListener.h"

#include "Audio/Audio.h"

namespace Volund
{
    void AudioListener::SetPosition(const Vec3& Position)
    {
        alCall(alListener3f, AL_POSITION,
            Position.x, Position.y, Position.z);
    }

    void AudioListener::SetOrientation(const Vec3& Front, const Vec3& Up)
    {
        ALfloat Orientation[] = { Front.x, Front.y, Front.z,
            Up.x, Up.y, Up.z };
        alCall(alListenerfv, AL_ORIENTATION, Orientation);
    }

    void AudioListener::SetVelocity(const Vec3& Velocity)
    {
        alCall(alListener3f, AL_VELOCITY, 
            Velocity.x, Velocity.y, Velocity.z);
    }

    AudioListener::AudioListener()
	{
        AudioListenerCount++;
        if (AudioListenerCount >= 2)
        {
            VOLUND_ERROR("Unable to create multiple AudioListeners!");
        }
	}

    AudioListener::~AudioListener()
    {
        AudioListenerCount--;
    }
}