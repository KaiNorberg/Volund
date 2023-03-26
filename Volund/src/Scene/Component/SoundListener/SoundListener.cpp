#include "PCH/PCH.h"

#include "SoundListener.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void SoundListener::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (e.Type)
		{
		case EventType::Update:
		{		
			static Vec3 oldPosition = Vec3(0.0f);

			const float timeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const Ref<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->m_Listener.SetPosition(entityTransform->Position);
			this->m_Listener.SetVelocity((entityTransform->Position - oldPosition) * timeStep);

			this->m_Listener.SetOrientation(entityTransform->GetFront(), entityTransform->GetUp());
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
