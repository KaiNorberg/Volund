#include "PCH/PCH.h"

#include "PointLight.h"

namespace Volund
{
	VML PointLight::Serialize()
	{
		VML PointLightVML;

		PointLightVML.PushBack("Type", VMLEntry("PointLight"));

		PointLightVML.PushBack("Color", VMLEntry({ this->Color.r, this->Color.g, this->Color.b }));

		PointLightVML.PushBack("Brightness", VMLEntry(this->Brightness));

		return PointLightVML;
	}

	PointLight::PointLight(RGB Color, float Brightness)
	{
		this->Color = Color;
		this->Brightness = Brightness;
	}
}
