
#include "PointLight.h"

//#include "Rendering/Renderer.h"

#include "Scene/Scene.h"
#include "Scene/Component/Transform/Transform.h"

namespace Volund
{
	void PointLight::Procedure(const Event& e)
	{
		
	}

	PointLight::PointLight(const RGB& color, float brighness)
	{
		this->color = color;
		this->brightness = brighness;
	}
}
