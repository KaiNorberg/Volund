#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion = Quat(Utils::ToRadians(rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		VOLUND_PROFILE_FUNCTION();

		return Utils::ToDegrees(eulerAngles(this->Quaternion));
	}

	void Transform::AddRotation(const Vec3& rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion *= Quat(Utils::ToRadians(rotation));
	}

	Vec3 Transform::GetFront() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Utils::BACK;
	}

	Vec3 Transform::GetRight() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Utils::RIGHT;
	}

	Vec3 Transform::GetUp() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Utils::UP;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		VOLUND_PROFILE_FUNCTION();

		Mat4x4 modelMatrix = Mat4x4(1.0f);

		modelMatrix = translate(modelMatrix, this->Position);
		modelMatrix *= Mat4x4(this->Quaternion);
		modelMatrix = scale(modelMatrix, this->Scale);

		return modelMatrix;
	}


	Transform::Transform()
	{

	}
}
