#include "PCH/PCH.h"
#include "AudioDevice.h"

#include "Audio/Audio.h"

namespace Volund
{
	ALCdevice* AudioDevice::GetDevice() const
	{
		return this->_Device;
	}

	AudioDevice::AudioDevice(const char* Device)
	{
		VOLUND_INFO("Retriving audio device %d...", Device);

		this->_Device = alcOpenDevice(Device);
		if (!this->_Device)
		{
			VOLUND_ERROR("Unable to open alc device!");
		}
	}

	AudioDevice::~AudioDevice()
	{
		ALCboolean Successful;
		if (!alcCall(alcCloseDevice, Successful, this->_Device, this->_Device))
		{
			//Do nothing
		}
	}
}