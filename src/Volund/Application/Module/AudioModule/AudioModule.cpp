#include "AudioModule.h"

#include "Audio/Audio.h"

namespace Volund
{
	void AudioModule::OnAttach(Application* app)
	{
		this->m_Device = std::make_shared<AudioDevice>(nullptr);
		this->m_Context = std::make_shared<AudioContext>(this->m_Device);
	}

	void AudioModule::OnDetach()
	{

	}

	void AudioModule::Procedure(const Event& e)
	{

	}
}
