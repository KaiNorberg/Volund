#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion = Quat(Math::Radians(rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		VOLUND_PROFILE_FUNCTION();

		return Math::Degress(this->Quaternion.EulerAngles());
	}

	void Transform::AddRotation(const Vec3& rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion *= Quat(Math::Radians(rotation));
	}

	Vec3 Transform::GetFront() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Math::BACK;
	}

	Vec3 Transform::GetRight() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Math::RIGHT;
	}

	Vec3 Transform::GetUp() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Math::UP;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		VOLUND_PROFILE_FUNCTION();

		Mat4x4 modelMatrix = Mat4x4(1.0f);

		modelMatrix = Math::Translate(modelMatrix, this->Position);
		modelMatrix *= Mat4x4(glm::mat4x4(glm::quat(this->Quaternion.w, this->Quaternion.x, this->Quaternion.y, this->Quaternion.z)));
		modelMatrix = Math::Scale(modelMatrix, this->Scale);

		return modelMatrix;
	}


	Transform::Transform()
	{

	}
}
