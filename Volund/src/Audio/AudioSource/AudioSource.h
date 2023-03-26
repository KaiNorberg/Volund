#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
	class AudioSource
	{
	public:

		void Play();

		void SetBuffer(Ref<AudioBuffer> buffer);

		void SetPitch(float pitch);

		void SetPosition(const Vec3& position);

		void SetDirection(const Vec3& direction);

		void SetVelocity(const Vec3& velocity);

		void SetLooping(bool looping);

		void SetGain(float gain);

		AudioSource();

		~AudioSource();

	private:

		Ref<AudioBuffer> m_Buffer;

		uint32_t m_Source;
	};
}