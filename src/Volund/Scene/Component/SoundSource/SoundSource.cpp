
#include "SoundSource.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void SoundSource::Play()
	{
		this->m_source.Play();
	}

	void SoundSource::SetBuffer(std::shared_ptr<AudioBuffer> buffer)
	{
		this->m_source.SetBuffer(buffer);
	}

	std::shared_ptr<AudioBuffer> SoundSource::GetBuffer()
	{
		return this->m_source.GetBuffer();
	}

	void SoundSource::SetPitch(float pitch)
	{
		this->m_source.SetPitch(pitch);
	}

	float SoundSource::GetPitch()
	{
		return this->m_source.GetPitch();
	}

	void SoundSource::SetLooping(bool looping)
	{
		this->m_source.SetLooping(looping);
	}

	bool SoundSource::GetLooping()
	{
		return this->m_source.GetLooping();
	}

	void SoundSource::SetGain(float gain)
	{
		this->m_source.SetGain(gain);
	}

	float SoundSource::GetGain()
	{
		return this->m_source.GetGain();
	}

	void SoundSource::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.type)
		{
		case VOLUND_EVENT_UPDATE:
		{
			if (this->AutoPlay && !this->m_hasAutoPlayed)
			{
				this->m_hasAutoPlayed = true;
				this->Play();
			}

			static Vec3 oldPosition = Vec3(0.0f);

			const float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->m_source.SetPosition(entityTransform->Position);
			this->m_source.SetVelocity((entityTransform->Position - oldPosition) * timeStep);
			this->m_source.SetDirection(entityTransform->GetFront());
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
