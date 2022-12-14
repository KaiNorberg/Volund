#include "PCH/PCH.h"
#include "LuaPointLight.h"

#include "Core/Scene/Component/Components.h"

namespace Volund
{
	LuaVec3 LuaPointLight::GetColor()
	{
		return this->_PointLight->Color;
	}

	void LuaPointLight::SetColor(LuaVec3 Color)
	{
		this->_PointLight->Color = Color;
	}

	void LuaPointLight::SetBrightness(float Brightness)
	{
		this->_PointLight->Brightness = Brightness;
	}

	float LuaPointLight::GetBrightness()
	{
		return this->_PointLight->Brightness;
	}

	LuaPointLight::LuaPointLight(Ref<PointLight> PointLight)
	{
		this->_PointLight = PointLight;
	}
}