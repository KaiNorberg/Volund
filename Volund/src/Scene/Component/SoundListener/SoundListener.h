#pragma once

#include "../Component.h"

#include "Audio/AudioListener/AudioListener.h"

namespace Volund
{
	class SoundListener : public Component
	{
	public:

		void Procedure(const Event& E);

		SoundListener() = default;

	private:

		AudioListener _Listener;
	};
}
