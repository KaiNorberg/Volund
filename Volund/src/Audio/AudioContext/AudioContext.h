#pragma once

#include "Audio/AudioDevice/AudioDevice.h"

struct ALCcontext;

namespace Volund
{
	class AudioContext
	{
	public:

		ALCcontext* GetContext() const;

		void MakeCurrent();

		AudioContext(const AudioDevice& Device);

		AudioContext(Ref<AudioDevice> Device);

		~AudioContext();

	private:

		ALCdevice* _Device;
		ALCcontext* _Context;
	};
}