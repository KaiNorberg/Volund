#pragma once

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaComponent/LuaComponents.h"
#include "Lua/LuaVec/LuaVec.h"

#include "Scene/Component/PointLight/PointLight.h"

namespace Volund
{
	struct LuaPointLight
	{
	public:

		int Padding;

		LuaVec3 GetColor();
		void SetColor(LuaVec3 Color);

		void SetBrightness(float Brightness);
		float GetBrightness();

		LuaPointLight(Ref<PointLight> PointLight);

	private:

		Ref<PointLight> _PointLight;
	};
}