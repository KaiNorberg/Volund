#pragma once

#include "../Component.h"

#include "Audio/AudioSource/AudioSource.h"

namespace Volund
{
	class SoundSource : public Component
	{
	public:

		void Play();

		void SetBuffer(Ref<AudioBuffer> buffer);

		void SetPitch(float pitch);

		void SetLooping(bool looping);

		void SetGain(float gain);

		void Procedure(const Event& e);

		SoundSource() = default;

	private:

		AudioSource m_Source;
	};
}
