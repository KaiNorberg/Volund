#include "PCH/PCH.h"

#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion = Quat(Math::Radians(rotation).GLM());
	}

	Vec3 Transform::GetRotation() const
	{
		VOLUND_PROFILE_FUNCTION();

		return glm::degrees(eulerAngles(this->Quaternion));
	}

	void Transform::AddRotation(const Vec3& rotation)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Quaternion *= Quat(Math::Radians(rotation).GLM());
	}

	Vec3 Transform::GetFront() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Math::BACK.GLM();
	}

	Vec3 Transform::GetRight() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Math::RIGHT.GLM();
	}

	Vec3 Transform::GetUp() const
	{
		VOLUND_PROFILE_FUNCTION();

		return this->Quaternion * Math::UP.GLM();
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		VOLUND_PROFILE_FUNCTION();

		Mat4x4 modelMatrix = Mat4x4(1.0f);

		auto test = glm::mat<4, 4, float>(1.0) * glm::vec<4, float>();

		modelMatrix = Math::Translate(modelMatrix, this->Position);
		//modelMatrix *= Mat4x4(this->Quaternion);
		modelMatrix = Math::Scale(modelMatrix, this->Scale);

		return modelMatrix;
	}


	Transform::Transform()
	{

	}
}
