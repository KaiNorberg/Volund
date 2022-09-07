#pragma once

#include "PCH/PCH.h"

#include "CameraMovement.h"

#include "Input/Input.h"
#include "Scene/Entity/Component/Transform/Transform.h"

#include "Scene/Entity/Entity.h"

namespace Volund
{
	JSON CameraMovement::Serialize()
	{
		JSON CameraMovementJSON;

		CameraMovementJSON.AddEntry("Type", "CameraMovement");

		CameraMovementJSON.AddEntry("Speed", this->Speed);
		CameraMovementJSON.AddEntry("Sensitivity", this->Sensitivity);

		return CameraMovementJSON;
	}

	void CameraMovement::OnUpdate(TimeStep TS)
	{
		Ref<Transform> EntityTransform = this->GetEntity()->GetComponent<Transform>();

		if (Input::IsHeld('W'))
		{
			EntityTransform->Position += EntityTransform->GetFront() * float(TS) * this->Speed;
		}
		if (Input::IsHeld('S'))
		{
			EntityTransform->Position -= EntityTransform->GetFront() * float(TS) * this->Speed;
		}
		if (Input::IsHeld('A'))
		{
			EntityTransform->Position -= EntityTransform->GetRight() * float(TS) * this->Speed;
		}
		if (Input::IsHeld('D'))
		{
			EntityTransform->Position += EntityTransform->GetRight() * float(TS) * this->Speed;
		}

		DVec2 Delta = Input::GetCursorPosition() - this->OldCursorPosition;
		Delta.x = Math::Clamp(Delta.x, -10.0, 10.0);
		Delta.y = Math::Clamp(Delta.y, -10.0, 10.0);

		Rotation -= Vec3(Delta.y, Delta.x, 0.0f);
		Rotation.x = Math::Clamp(Rotation.x, -89.0f, 89.0f);

		EntityTransform->SetRotation(Rotation * this->Sensitivity);
		this->OldCursorPosition = Input::GetCursorPosition();
	}

	CameraMovement::CameraMovement(float Speed, float Sensitivity)
	{
		this->OldCursorPosition = Input::GetCursorPosition();

		this->Speed = Speed;

		this->Sensitivity = Sensitivity;
	}
}