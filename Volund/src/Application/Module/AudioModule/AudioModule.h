#pragma once

#include "../Module.h"

#include "Audio/AudioDevice/AudioDevice.h"
#include "Audio/AudioContext/AudioContext.h"

namespace Volund
{
	class AudioModule : public Module
	{
	public:

		void OnAttach(Application* app) override;

		void OnDetach() override;

		void Procedure(const Event& e) override;

	private:	

		Ref<AudioDevice> m_Device;
		Ref<AudioContext> m_Context;
	};
}