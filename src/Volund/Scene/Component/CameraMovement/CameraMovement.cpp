
#include "CameraMovement.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void CameraMovement::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_input.Procedure(e);

		switch (e.type)
		{
		case VOLUND_EVENT_UPDATE:
		{
			VOLUND_PROFILE_FUNCTION();

			const float ts = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			if (m_input.IsHeld('W'))
			{
				entityTransform->Position += entityTransform->GetFront() * float(ts) * this->Speed;
			}
			if (m_input.IsHeld('S'))
			{
				entityTransform->Position -= entityTransform->GetFront() * float(ts) * this->Speed;
			}
			if (m_input.IsHeld('A'))
			{
				entityTransform->Position -= entityTransform->GetRight() * float(ts) * this->Speed;
			}
			if (m_input.IsHeld('D'))
			{
				entityTransform->Position += entityTransform->GetRight() * float(ts) * this->Speed;
			}

			IVec2 delta = m_input.GetMousePosition() - this->m_oldMousePosition;

			delta.x = std::clamp(delta.x, -10, 10) * this->Sensitivity;
			delta.y = std::clamp(delta.y, -10, 10) * this->Sensitivity;

			m_rotation -= Vec3(delta.y, delta.x, 0.0f) * this->Sensitivity;
			m_rotation.x = std::clamp(m_rotation.x, -89.0f, 89.0f);

			entityTransform->SetRotation(m_rotation);
			this->m_oldMousePosition = m_input.GetMousePosition();
		}
		break;
		default:
		{

		}
		break;
		}
	}

	void CameraMovement::OnCreate()
	{
		this->m_oldMousePosition = m_input.GetMousePosition();
	}
}
