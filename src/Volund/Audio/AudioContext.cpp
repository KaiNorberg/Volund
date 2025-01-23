#include "Audio/AudioContext.hpp"

#include "Audio/Audio.hpp"
#include "Logger.hpp"

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
	ALCcontext* AudioContext::GetContext() const
	{
		return this->m_context;
	}

	void AudioContext::MakeCurrent()
	{
		ALCboolean successful = false;
		if (!ALC_CALL(alcMakeContextCurrent, successful, this->m_device, this->m_context) || successful != ALC_TRUE)
		{
			VOLUND_ERROR("Unable to make alc context current!");
		}
	}

	AudioContext::AudioContext(const AudioDevice& device)
	{
		this->m_device = device.GetDevice();

		if (!ALC_CALL(alcCreateContext, this->m_context, this->m_device, this->m_device, nullptr) || !this->m_context)
		{
			VOLUND_ERROR("Unable to create alc context!");
		}
	}

	AudioContext::AudioContext(std::shared_ptr<AudioDevice> device)
	{
		this->m_device = device->GetDevice();

		if (!ALC_CALL(alcCreateContext, this->m_context, this->m_device, this->m_device, nullptr) || !this->m_context)
		{
			VOLUND_ERROR("Unable to create alc context!");
		}

		this->MakeCurrent();

		VOLUND_INFO("OpenAL Renderer: {}", alGetString(AL_RENDERER));
		VOLUND_INFO("OpenAL Version: {}", alGetString(AL_VERSION));
		VOLUND_INFO("OpenAL Vendor: {}", alGetString(AL_VENDOR));
	}

	AudioContext::~AudioContext()
	{
		this->MakeCurrent();

		if (!ALC_CALL(alcDestroyContext, this->m_device, this->m_context))
		{
			VOLUND_ERROR("Unable to destroy alc context!");
		}
	}
}