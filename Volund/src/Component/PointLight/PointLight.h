#pragma once

#include "Component/Component.h"

namespace Volund
{
	class PointLight : public Component
	{
	public:
		
		RGB Color;

		PointLight(RGB Color = RGB(1.0f));

	private:

	};

} //namespace Volund