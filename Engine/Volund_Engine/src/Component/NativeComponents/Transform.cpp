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
		return this->Front;
	}

	Vec3 Transform::GetRight()
	{
		return this->Right;
	}

	Vec3 Transform::GetUp()
	{
		return this->Up;
	}

	void Transform::Update()
	{
		this->Front = this->Quaternion * Math::Back; //Dont ask
		this->Right = this->Quaternion * Math::Right;
		this->Up = this->Quaternion * Math::Up;
	}

	const std::string Transform::Type()
	{
		return TRANSFORM_COMPONENT;
	}

	Transform::Transform(Entity* Parent, JSON ComponentJSON)
	{
		this->Parent = Parent;

		if (ComponentJSON.contains("Position"))
		{
			JSON JSONPosition = ComponentJSON["Position"];
			if (JSONPosition.is_array() && JSONPosition.size() == 3)
			{
				this->Position.x = JSONPosition[0];
				this->Position.y = JSONPosition[1];				
				this->Position.z = JSONPosition[2];
			}
		}
		if (ComponentJSON.contains("Scale"))
		{
			JSON JSONScale = ComponentJSON["Scale"];
			if (JSONScale.is_array() && JSONScale.size() == 3)
			{
				this->Scale.x = JSONScale[0];
				this->Scale.y = JSONScale[1];				
				this->Scale.z = JSONScale[2];
			}
		}
	}
}

