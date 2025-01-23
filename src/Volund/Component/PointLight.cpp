
#include "Component/PointLight.hpp"

#include "Rendering/Renderer.hpp"
#include "Lua/LuaAPI.hpp"
#include "Scene.hpp"
#include "Component/Transform.hpp"

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