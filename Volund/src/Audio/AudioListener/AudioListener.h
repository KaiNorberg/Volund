#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
	class AudioListener
	{
	public:

		void SetPosition(const Vec3& Position);

		void SetOrientation(const Vec3& Front, const Vec3& Up);

		void SetVelocity(const Vec3& Velocity);

		AudioListener();

		~AudioListener();

	private:
		
		static inline uint32_t AudioListenerCount = 0;
	};
}