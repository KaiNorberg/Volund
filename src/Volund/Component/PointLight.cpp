
#include "Component/PointLight.h"

#include "Rendering/Renderer.h"

#include "Scene.h"
#include "Component/Transform.h"

namespace Volund
{
	void PointLight::Procedure(const Event& e)
	{
		
	}

	PointLight::PointLight(const RGB& color, float brightness)
	{
		this->color = color;
		this->brightness = brightness;
	}
}