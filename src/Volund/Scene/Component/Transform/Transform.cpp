
#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& rotation)
	{
		this->Quaternion = Quat(Math::Radians(rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		return Math::Degress(this->Quaternion.EulerAngles());
	}

	void Transform::AddRotation(const Vec3& rotation)
	{
		this->Quaternion *= Quat(Math::Radians(rotation));
	}

	Vec3 Transform::GetFront() const
	{
		return this->Quaternion * Math::BACK;
	}

	Vec3 Transform::GetRight() const
	{
		return this->Quaternion * Math::RIGHT;
	}

	Vec3 Transform::GetUp() const
	{
		return this->Quaternion * Math::UP;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		Mat4x4 modelMatrix = Mat4x4(1.0f);

		modelMatrix = Math::Translate(modelMatrix, this->Position);
		modelMatrix *= Mat4x4(this->Quaternion);
		modelMatrix = Math::Scale(modelMatrix, this->Scale);

		return modelMatrix;
	}


	Transform::Transform()
	{

	}
}
