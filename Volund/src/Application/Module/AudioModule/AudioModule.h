#pragma once

#include "../Module.h"

#include "Audio/AudioDevice/AudioDevice.h"
#include "Audio/AudioContext/AudioContext.h"

namespace Volund
{
	class AudioModule : public Module
	{
	public:

		void OnAttach(Application* App) override;

		void OnDetach() override;

		void Procedure(const Event& E) override;

	private:	

		Ref<AudioDevice> _Device;
		Ref<AudioContext> _Context;
	};
}