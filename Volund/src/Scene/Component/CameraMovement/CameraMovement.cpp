#include "PCH/PCH.h"

#include "CameraMovement.h"

#include "Scene/Component/Transform/Transform.h"

#include "Scene/Scene.h"

namespace Volund
{
	void CameraMovement::OnEvent(Event* E)
	{
		this->_Input.HandleEvent(E);
	}

	void CameraMovement::OnUpdate(TimeStep TS)
	{
		Ref<Transform> EntityTransform = VL::Scene::GetComponent<Transform>(this->GetEntity());

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

		IVec2 Delta = _Input.GetMousePosition() - this->_OldMousePosition;

		Delta.x = (int32_t)((float)Math::Clamp(Delta.x, -10, 10) * this->Sensitivity);
		Delta.y = (int32_t)((float)Math::Clamp(Delta.y, -10, 10) * this->Sensitivity);

		_Rotation -= Vec3(Delta.y, Delta.x, 0.0f) * this->Sensitivity;
		_Rotation.x = Math::Clamp(_Rotation.x, -89.0f, 89.0f);

		EntityTransform->SetRotation(_Rotation);
		this->_OldMousePosition = _Input.GetMousePosition();
	}

	CameraMovement::CameraMovement()
	{
		this->_OldMousePosition = _Input.GetMousePosition();
	}
}
