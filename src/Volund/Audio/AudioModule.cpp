#include "Audio/AudioModule.hpp"

#include "Audio/Audio.hpp"

namespace Volund
{
	void AudioModule::OnAttach(Application* app)
	{
		this->m_device = std::make_shared<AudioDevice>(nullptr);
		this->m_context = std::make_shared<AudioContext>(this->m_device);
	}

	void AudioModule::OnDetach()
	{

	}

	void AudioModule::Procedure(const Event& e)
	{

	}
}