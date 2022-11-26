#pragma once

#include "../Component.h"

namespace Volund
{
	class PointLight : public Component
	{
	public:
		RGB Color = RGB(1.0f);

		float Brightness = 1.0f;

		void OnUpdate(TimeStep TS);

		VML Serialize() override;

		PointLight();

	private:
	};
} //namespace Volund
