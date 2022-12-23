#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& Rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion = Quat(Utils::ToRadians(Rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		VOLUND_PROFILE_FUNCTION();

		return Utils::ToDegrees(eulerAngles(this->Quaternion));
	}

	void Transform::AddRotation(const Vec3& Rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion *= Quat(Utils::ToRadians(Rotation));
	}

	Vec3 Transform::GetFront() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Utils::Back;
	}

	Vec3 Transform::GetRight() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Utils::Right;
	}

	Vec3 Transform::GetUp() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Utils::Up;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		VOLUND_PROFILE_FUNCTION();

		Mat4x4 ModelMatrix = Mat4x4(1.0f);

		ModelMatrix = translate(ModelMatrix, this->Position);
		ModelMatrix *= Mat4x4(this->Quaternion);
		ModelMatrix = scale(ModelMatrix, this->Scale);

		return ModelMatrix;
	}

	void Transform::OnUpdate(TimeStep TS)
	{
		VOLUND_PROFILE_FUNCTION();
	}

	Transform::Transform()
	{
		this->OnUpdate(0.0f);
	}
}
