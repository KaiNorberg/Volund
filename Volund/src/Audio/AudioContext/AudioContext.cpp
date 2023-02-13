#include "PCH/PCH.h"
#include "AudioContext.h"

#include "Audio/Audio.h"

namespace Volund
{
	ALCcontext* AudioContext::GetContext() const
	{
		return this->_Context;
	}

	void AudioContext::MakeCurrent()
	{
		ALCboolean Successful = false;
		if (!alcCall(alcMakeContextCurrent, Successful, this->_Device, this->_Context) || Successful != ALC_TRUE)
		{
			VOLUND_ERROR("Unable to make alc context current!");
		}
	}

	AudioContext::AudioContext(const AudioDevice& Device)
	{
		this->_Device = Device.GetDevice();

		if (!alcCall(alcCreateContext, this->_Context, this->_Device, this->_Device, nullptr) || !this->_Context)
		{
			VOLUND_ERROR("Unable to create alc context!");
		}
	}

	AudioContext::AudioContext(Ref<AudioDevice> Device)
	{
		this->_Device = Device->GetDevice();

		if (!alcCall(alcCreateContext, this->_Context, this->_Device, this->_Device, nullptr) || !this->_Context)
		{
			VOLUND_ERROR("Unable to create alc context!");
		}
	}

	AudioContext::~AudioContext()
	{
		this->MakeCurrent();

		if (!alcCall(alcDestroyContext, this->_Device, this->_Context))
		{
			VOLUND_ERROR("Unable to destroy alc context!");
		}
	}
}