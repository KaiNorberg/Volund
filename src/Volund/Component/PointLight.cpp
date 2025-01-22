
#include "Component/PointLight.h"

#include "Rendering/Renderer.h"
#include "Lua/LuaAPI.h"
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

    VOLUND_USERTYPE_COMPONENT_REGISTER(PointLight,
    [](LuaState* state){
        state->NewUsertype<PointLight>("PointLight", 
            sol::constructors<>(),
            "color", &PointLight::color,
            "brightness", &PointLight::brightness
        );
    }, const RGB&, float);
}