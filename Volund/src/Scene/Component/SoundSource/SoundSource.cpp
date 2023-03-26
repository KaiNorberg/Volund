#include "PCH/PCH.h"

#include "SoundSource.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void SoundSource::Play()
	{
		this->m_Source.Play();
	}

	void SoundSource::SetBuffer(Ref<AudioBuffer> buffer)
	{
		this->m_Source.SetBuffer(buffer);
	}

	void SoundSource::SetPitch(float pitch)
	{
		this->m_Source.SetPitch(pitch);
	}

	void SoundSource::SetLooping(bool looping)
	{
		this->m_Source.SetLooping(looping);
	}

	void SoundSource::SetGain(float gain)
	{
		this->m_Source.SetGain(gain);
	}

	void SoundSource::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Update:
		{		
			static Vec3 oldPosition = Vec3(0.0f);

			const float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const Ref<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->m_Source.SetPosition(entityTransform->Position);
			this->m_Source.SetVelocity((entityTransform->Position - oldPosition) * timeStep);
			this->m_Source.SetDirection(entityTransform->GetFront());
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
