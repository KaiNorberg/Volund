#pragma once

#include "Lua/LuaComponent/LuaComponent.h"

#include "Scene/Component/Camera/Camera.h"

namespace Volund
{
	struct LuaCamera
	{
	public:

		float GetFOV();
		void SetFOV(float FOV);

		float GetNearPlane();
		void SetNearPlane(float NearPlane);

		float GetFarPlane();
		void SetFarPlane(float FarPlane);

		LuaCamera(Ref<Camera> Camera);

	private:

		Ref<Camera> _Camera;
	};
}