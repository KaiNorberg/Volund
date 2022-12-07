#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& Rotation)
	{
		this->Quaternion = Quat(Utils::ToRadians(Rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		return Utils::ToDegrees(eulerAngles(this->Quaternion));
	}

	void Transform::AddRotation(const Vec3& Rotation)
	{
		this->Quaternion *= Quat(Utils::ToRadians(Rotation));
	}

	Vec3 Transform::GetFront() const
	{
		return this->_Front;
	}

	Vec3 Transform::GetRight() const
	{
		return this->_Right;
	}

	Vec3 Transform::GetUp() const
	{
		return this->_Up;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		return this->_ModelMatrix;
	}

	void Transform::OnUpdate(TimeStep TS)
	{
		this->_Front = this->Quaternion * Utils::Back; //Dont ask
		this->_Right = this->Quaternion * Utils::Right;
		this->_Up = this->Quaternion * Utils::Up;

		this->_ModelMatrix = Mat4x4(1.0f);

		this->_ModelMatrix = translate(this->_ModelMatrix, this->Position);
		this->_ModelMatrix *= Mat4x4(this->Quaternion);
		this->_ModelMatrix = scale(this->_ModelMatrix, this->Scale);
	}

	Transform::Transform()
	{
		this->OnUpdate(0.0f);
	}
}
