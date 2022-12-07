#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

#include "Core/Scene/Component/Camera/Camera.h"

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

		bool IsActive();
		void SetActive();

		LuaCamera(Ref<Camera> Camera);

	private:

		Ref<Camera> _Camera;
	};
}