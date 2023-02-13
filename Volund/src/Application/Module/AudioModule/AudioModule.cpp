#include "PCH/PCH.h"
#include "AudioModule.h"

#include "Audio/Audio.h"

namespace Volund
{
	void AudioModule::OnAttach(Application* App)
	{
		const char* AL_DefaultDeviceString = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);

		this->_Device = std::make_shared<AudioDevice>(AL_DefaultDeviceString);
		this->_Context = std::make_shared<AudioContext>(this->_Device);
		this->_Context->MakeCurrent();

		VOLUND_INFO("OpenAL Renderer: %s", alGetString(AL_RENDERER));
		VOLUND_INFO("OpenAL Version: %s", alGetString(AL_VERSION));
		VOLUND_INFO("OpenAL Vendor: %s", alGetString(AL_VENDOR));
	}

	void AudioModule::OnDetach()
	{

	}

	void AudioModule::Procedure(const Event& E)
	{

	}
}