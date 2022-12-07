#include "PCH/PCH.h"
#include "LuaCameraMovement.h"

namespace Volund
{
	float LuaCameraMovement::GetSpeed()
	{
		return this->_CameraMovement->Speed;
	}

	void LuaCameraMovement::SetSpeed(float Speed)
	{
		this->_CameraMovement->Speed = Speed;
	}

	float LuaCameraMovement::GetSensitivity()
	{
		return this->_CameraMovement->Sensitivity;
	}

	void LuaCameraMovement::SetSensitivity(float Sensitivity)
	{
		this->_CameraMovement->Sensitivity = Sensitivity;
	}

	LuaCameraMovement::LuaCameraMovement(Ref<CameraMovement> CameraMovement)
	{
		this->_CameraMovement = CameraMovement;
	}
}