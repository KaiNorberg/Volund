#pragma once

#include "Lua/LuaComponent/LuaComponent.h"
#include "Lua/LuaComponent/LuaComponents.h"

#include "Scene/Component/CameraMovement/CameraMovement.h"

namespace Volund
{
	struct LuaCameraMovement
	{
	public:

		float GetSpeed();
		void SetSpeed(float Speed);

		float GetSensitivity();
		void SetSensitivity(float Sensitivity);

		LuaCameraMovement(Ref<CameraMovement> CameraMovement);

	private:

		Ref<CameraMovement> _CameraMovement;
	};
}