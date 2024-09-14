#include "PCH/PCH.h"

#include "CameraMovement.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void CameraMovement::Procedure(const Event& e)
	{
		VOLUND_PROFILE_FUNCTION();

		this->m_Input.Procedure(e);

		switch (e.type)
		{
		case VOLUND_EVENT_UPDATE:
		{
			VOLUND_PROFILE_FUNCTION();

			const float ts = VOLUND_EVENT_UPDATE_GET_TIMESTEP(e);

			const std::shared_ptr<Transform> entityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			if (m_Input.IsHeld('W'))
			{
				entityTransform->Position += entityTransform->GetFront() * float(ts) * this->Speed;
			}
			if (m_Input.IsHeld('S'))
			{
				entityTransform->Position -= entityTransform->GetFront() * float(ts) * this->Speed;
			}
			if (m_Input.IsHeld('A'))
			{
				entityTransform->Position -= entityTransform->GetRight() * float(ts) * this->Speed;
			}
			if (m_Input.IsHeld('D'))
			{
				entityTransform->Position += entityTransform->GetRight() * float(ts) * this->Speed;
			}

			IVec2 delta = m_Input.GetMousePosition() - this->m_OldMousePosition;

			delta.x = std::clamp(delta.x, -10, 10) * this->Sensitivity;
			delta.y = std::clamp(delta.y, -10, 10) * this->Sensitivity;

			m_Rotation -= Vec3(delta.y, delta.x, 0.0f) * this->Sensitivity;
			m_Rotation.x = std::clamp(m_Rotation.x, -89.0f, 89.0f);

			entityTransform->SetRotation(m_Rotation);
			this->m_OldMousePosition = m_Input.GetMousePosition();
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
		this->m_OldMousePosition = m_Input.GetMousePosition();
	}
}
