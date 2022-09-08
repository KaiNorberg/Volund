#pragma once

#include "../Component.h"

#include "Input/Input.h"

namespace Volund
{
	class CameraMovement : public Component
	{
	public:
		float Speed = 1.0f;

		float Sensitivity = 1.0f;

		void OnEvent(Event* E) override;

		void OnUpdate(TimeStep TS) override;

		JSON Serialize() override;

		CameraMovement(float Speed = 1.0f, float Sensitivity = 1.0f);

	private:
		Input _Input;

		Vec3 _Rotation = Vec3(0.0f);

		IVec2 _OldMousePosition = Vec2(0.0f);
	};
} //namespace Volund
