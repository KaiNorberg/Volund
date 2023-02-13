#pragma once

#include "../Component.h"

#include "Audio/AudioSource/AudioSource.h"

namespace Volund
{
	class SoundSource : public Component
	{
	public:

		void Play();

		void SetBuffer(Ref<AudioBuffer> Buffer);

		void SetPitch(float Pitch);

		void SetLooping(bool Looping);

		void SetGain(float Gain);

		void Procedure(const Event& E);

		SoundSource() = default;

	private:

		AudioSource _Source;
	};
}
