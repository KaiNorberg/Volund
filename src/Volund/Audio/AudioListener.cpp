#include "Audio/AudioListener.hpp"

#include "Audio/Audio.hpp"

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
    void AudioListener::SetPosition(const Vec3& position)
    {
        AL_CALL(alListener3f, AL_POSITION,
            position.x, position.y, position.z);
    }

    void AudioListener::SetOrientation(const Vec3& front, const Vec3& up)
    {
        ALfloat orientation[] = { front.x, front.y, front.z,
            up.x, up.y, up.z };
        AL_CALL(alListenerfv, AL_ORIENTATION, orientation);
    }

    void AudioListener::SetVelocity(const Vec3& velocity)
    {
        AL_CALL(alListener3f, AL_VELOCITY,
            velocity.x, velocity.y, velocity.z);
    }

    AudioListener::AudioListener()
	{
        m_audioListenerCount++;
        if (m_audioListenerCount >= 2)
        {
            VOLUND_ERROR("Unable to create multiple AudioListeners!");
        }
	}

    AudioListener::~AudioListener()
    {
        m_audioListenerCount--;
    }
}