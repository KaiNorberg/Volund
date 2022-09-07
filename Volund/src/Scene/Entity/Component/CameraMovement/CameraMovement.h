#pragma once

#include "../Component.h"

namespace Volund
{
	class CameraMovement : public Component
	{
	public:
		
		float Speed = 1.0f;

		float Sensitivity = 1.0f;

		void OnUpdate(TimeStep TS) override;

		JSON Serialize() override;

		CameraMovement(float Speed = 1.0f, float Sensitivity = 1.0f);

	private:

		Vec3 Rotation = Vec3(0.0f);

		DVec2 OldCursorPosition = DVec2(0.0f);
	};

} //namespace Volund