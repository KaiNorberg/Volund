#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(Vec3 const& Rotation)
	{
		this->Quaternion = Quat(Math::ToRadians(Rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		return Math::ToDegrees(glm::eulerAngles(this->Quaternion));
	}

	void Transform::AddRotation(Vec3 const& Rotation)
	{
		this->Quaternion *= Quat(Math::ToRadians(Rotation));
	}

	Vec3 Transform::GetFront()
	{
		return this->_Front;
	}

	Vec3 Transform::GetRight()
	{
		return this->_Right;
	}

	Vec3 Transform::GetUp()
	{
		return this->_Up;
	}

	void Transform::OnUpdate(TimeStep TS)
	{
		this->_Front = this->Quaternion * Math::Back; //Dont ask
		this->_Right = this->Quaternion * Math::Right;
		this->_Up = this->Quaternion * Math::Up;
	}

	Transform::Transform(Vec3 const& Position, Vec3 const& Rotation, Vec3 const& Scale)
	{
		this->Position = Position;
		this->Scale = Scale;
		this->SetRotation(Rotation);
	}
}

