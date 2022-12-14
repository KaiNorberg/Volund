#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"
#include "Core/Lua/LuaVec/LuaVec.h"

#include "Core/Scene/Component/PointLight/PointLight.h"

namespace Volund
{
	struct LuaPointLight
	{
	public:

		LuaVec3 GetColor();
		void SetColor(LuaVec3 Color);

		void SetBrightness(float Brightness);
		float GetBrightness();

		LuaPointLight(Ref<PointLight> PointLight);

	private:

		Ref<PointLight> _PointLight;
	};
}