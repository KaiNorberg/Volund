#include "PCH/PCH.h"

#include "SoundListener.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void SoundListener::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		switch (E.Type)
		{
		case EventType::UPDATE:
		{		
			static Vec3 OldPosition = Vec3(0.0f);

			float TimeStep = VOLUND_EVENT_UPDATE_GET_TIMESTEP(E);

			Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			this->_Listener.SetPosition(EntityTransform->Position);
			this->_Listener.SetVelocity((EntityTransform->Position - OldPosition) * TimeStep);

			this->_Listener.SetOrientation(EntityTransform->GetFront(), EntityTransform->GetUp());
		}
		break;
		default:
		{

		}
		break;
		}
	}
}
