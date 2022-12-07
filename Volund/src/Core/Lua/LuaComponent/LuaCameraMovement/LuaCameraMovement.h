#pragma once

#include "Core/Lua/LuaComponent/LuaComponent.h"
#include "Core/Lua/LuaComponent/LuaComponents.h"

#include "Core/Scene/Component/CameraMovement/CameraMovement.h"

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