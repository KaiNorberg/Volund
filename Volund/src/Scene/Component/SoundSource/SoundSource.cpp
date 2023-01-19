#include "PCH/PCH.h"

#include "SoundSource.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void SoundSource::Play()
	{
		this->_Source.Play();
	}

	void SoundSource::SetBuffer(const AudioBuffer& Buffer)
	{
		this->_Source.SetBuffer(Buffer);
	}

	void SoundSource::SetBuffer(Ref<AudioBuffer> Buffer)
	{
		this->_Source.SetBuffer(Buffer);
	}

	void SoundSource::SetPitch(float Pitch)
	{
		this->_Source.SetPitch(Pitch);
	}

	void SoundSource::SetLooping(bool Looping)
	{
		this->_Source.SetLooping(Looping);
	}

	void SoundSource::SetGain(float Gain)
	{
		this->_Source.SetGain(Gain);
	}

	void SoundSource::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::UPDATE:
		{		
			static Vec3 OldPosition = Vec3(0.0f);

			Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->_Source.SetPosition(EntityTransform->Position);
			this->_Source.SetVelocity(EntityTransform->Position - OldPosition);
			this->_Source.SetDirection(EntityTransform->GetFront());
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
