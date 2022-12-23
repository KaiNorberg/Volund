#include "PCH/PCH.h"

#include "CameraMovement.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void CameraMovement::Procedure(const Event& E)
	{
		VOLUND_PROFILE_FUNCTION();

		this->_Input.HandleEvent(E);

		switch (E.Type)
		{
		case EventType::UPDATE:
		{
			VOLUND_PROFILE_FUNCTION();

			float TS = VOLUND_EVENT_UPDATE_GET_TIMESTEP(E);

			Ref<Transform> EntityTransform = this->GetScene()->GetComponent<Transform>(this->GetEntity());

			if (_Input.IsHeld('W'))
			{
				EntityTransform->Position += EntityTransform->GetFront() * float(TS) * this->Speed;
			}
			if (_Input.IsHeld('S'))
			{
				EntityTransform->Position -= EntityTransform->GetFront() * float(TS) * this->Speed;
			}
			if (_Input.IsHeld('A'))
			{
				EntityTransform->Position -= EntityTransform->GetRight() * float(TS) * this->Speed;
			}
			if (_Input.IsHeld('D'))
			{
				EntityTransform->Position += EntityTransform->GetRight() * float(TS) * this->Speed;
			}

			Vec2 Delta = _Input.GetMousePosition() - this->_OldMousePosition;

			Delta.x = ((float)Utils::Clamp(Delta.x, -10.0f, 10.0f) * this->Sensitivity);
			Delta.y = ((float)Utils::Clamp(Delta.y, -10.0f, 10.0f) * this->Sensitivity);

			_Rotation -= Vec3(Delta.y, Delta.x, 0.0f) * this->Sensitivity;
			_Rotation.x = Utils::Clamp(_Rotation.x, -89.0f, 89.0f);

			EntityTransform->SetRotation(_Rotation);
			this->_OldMousePosition = _Input.GetMousePosition();
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
		this->_OldMousePosition = _Input.GetMousePosition();
	}
}
