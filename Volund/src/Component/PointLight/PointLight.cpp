#pragma once

#include "PCH/PCH.h"

#include "PointLight.h"

namespace Volund
{
	JSON PointLight::Serialize()
	{
		JSON PointLightJSON;

		PointLightJSON.AddEntry("Type", "PointLight");

		PointLightJSON.AddList("Color", { this->Color.r, this->Color.g, this->Color.b });

		return PointLightJSON;
	}

	PointLight::PointLight(RGB Color)
	{
		this->Color = Color;
	}
}