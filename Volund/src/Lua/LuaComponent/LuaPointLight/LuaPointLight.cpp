#include "PCH/PCH.h"
#include "LuaPointLight.h"

#include "Scene/Component/Components.h"

namespace Volund
{
	Vec3 LuaPointLight::GetColor()
	{
		return this->_PointLight->Color;
	}

	void LuaPointLight::SetColor(Vec3 Color)
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