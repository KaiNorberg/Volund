#pragma once

#include "../Component.h"

namespace Volund
{
	class PointLight : public Component
	{
	public:
		RGB Color = RGB(1.0f);

		float Brightness = 1.0f;

		VML Serialize() override;

		PointLight(RGB Color = RGB(1.0f), float Brightness = 1.0f);

	private:
	};
} //namespace Volund
