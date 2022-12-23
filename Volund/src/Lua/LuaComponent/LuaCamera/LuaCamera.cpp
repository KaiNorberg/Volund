#include "PCH/PCH.h"
#include "LuaCamera.h"

namespace Volund
{
	float LuaCamera::GetFOV()
	{
		return this->_Camera->FOV;
	}

	void LuaCamera::SetFOV(float FOV)
	{
		this->_Camera->FOV = FOV;
	}

	float LuaCamera::GetNearPlane()
	{
		return this->_Camera->NearPlane;
	}

	void LuaCamera::SetNearPlane(float NearPlane)
	{
		this->_Camera->NearPlane = NearPlane;
	}

	float LuaCamera::GetFarPlane()
	{
		return this->_Camera->FarPlane;
	}

	void LuaCamera::SetFarPlane(float FarPlane)
	{
		this->_Camera->FarPlane = FarPlane;
	}

	LuaCamera::LuaCamera(Ref<Camera> Camera)
	{
		this->_Camera = Camera;
	}
}