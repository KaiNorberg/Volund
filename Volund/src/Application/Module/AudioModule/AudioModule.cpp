#include "PCH/PCH.h"
#include "AudioModule.h"

#include "Audio/Audio.h"

namespace Volund
{
	void AudioModule::OnAttach(Application* app)
	{
		const char* alDefaultDeviceString = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);

		this->m_Device = std::make_shared<AudioDevice>(alDefaultDeviceString);
		this->m_Context = std::make_shared<AudioContext>(this->m_Device);
		this->m_Context->MakeCurrent();

		//VOLUND_INFO("OpenAL Renderer: %s", alGetString(AL_RENDERER));
		//VOLUND_INFO("OpenAL Version: %s", alGetString(AL_VERSION));
		//VOLUND_INFO("OpenAL Vendor: %s", alGetString(AL_VENDOR));
	}

	void AudioModule::OnDetach()
	{

	}

	void AudioModule::Procedure(const Event& e)
	{

	}
}