#include "PCH/PCH.h"
#include "AudioContext.h"

#include "Audio/Audio.h"

namespace Volund
{
	ALCcontext* AudioContext::GetContext() const
	{
		return this->m_Context;
	}

	void AudioContext::MakeCurrent()
	{
		ALCboolean successful = false;
		if (!ALC_CALL(alcMakeContextCurrent, successful, this->m_Device, this->m_Context) || successful != ALC_TRUE)
		{
			VOLUND_ERROR("Unable to make alc context current!");
		}
	}

	AudioContext::AudioContext(const AudioDevice& device)
	{
		this->m_Device = device.GetDevice();

		if (!ALC_CALL(alcCreateContext, this->m_Context, this->m_Device, this->m_Device, nullptr) || !this->m_Context)
		{
			VOLUND_ERROR("Unable to create alc context!");
		}
	}

	AudioContext::AudioContext(Ref<AudioDevice> device)
	{
		this->m_Device = device->GetDevice();

		if (!ALC_CALL(alcCreateContext, this->m_Context, this->m_Device, this->m_Device, nullptr) || !this->m_Context)
		{
			VOLUND_ERROR("Unable to create alc context!");
		}
	}

	AudioContext::~AudioContext()
	{
		this->MakeCurrent();

		if (!ALC_CALL(alcDestroyContext, this->m_Device, this->m_Context))
		{
			VOLUND_ERROR("Unable to destroy alc context!");
		}
	}
}