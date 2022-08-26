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
		return Math::Euler(this->Quaternion);
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

	const std::string Transform::Type()
	{
		return VOLUND_COMPONENT_TRANSFORM;
	}

	Transform::Transform(Entity* Parent, JSON ComponentJSON)
	{
		this->_Parent = Parent;

		if (ComponentJSON.Contains("Position"))
		{
			JSON JSONPosition = ComponentJSON["Position"];
			this->Position.x = JSONPosition[0];
			this->Position.y = JSONPosition[1];
			this->Position.z = JSONPosition[2];
		}
		if (ComponentJSON.Contains("Scale"))
		{
			JSON JSONScale = ComponentJSON["Scale"];
			this->Scale.x = JSONScale[0];
			this->Scale.y = JSONScale[1];
			this->Scale.z = JSONScale[2];
		}
	}
}

