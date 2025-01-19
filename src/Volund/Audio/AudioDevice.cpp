#include "Audio/AudioDevice.h"

#include "Audio/Audio.h"
#include "Logger.h"

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
	ALCdevice* AudioDevice::GetDevice() const
	{
		return this->m_device;
	}

	AudioDevice::AudioDevice(std::string const& device)
	{
		VOLUND_INFO("Retriving audio device %d...", device.c_str());

		this->m_device = alcOpenDevice(device.c_str());
		if (!this->m_device)
		{
			VOLUND_ERROR("Unable to open alc device!");
		}
	}

	AudioDevice::~AudioDevice()
	{
		ALCboolean successful;
		if (!ALC_CALL(alcCloseDevice, successful, this->m_device, this->m_device))
		{
			//Do nothing
		}
	}
}