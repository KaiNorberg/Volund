#pragma once

#include "../Component.h"

namespace Volund
{
	class PointLight : public Component
	{
	public:
		RGB Color;

		JSON Serialize() override;

		PointLight(RGB Color = RGB(1.0f));

	private:
	};
} //namespace Volund
