#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
	class AudioSource
	{
	public:

		void Play();

		void SetBuffer(Ref<AudioBuffer> Buffer);

		void SetPitch(float Pitch);

		void SetPosition(const Vec3& Position);

		void SetDirection(const Vec3& Direction);

		void SetVelocity(const Vec3& Velocity);

		void SetLooping(bool Looping);

		void SetGain(float Gain);

		AudioSource();

		~AudioSource();

	private:

		Ref<AudioBuffer> _Buffer;

		uint32_t _Source;
	};
}