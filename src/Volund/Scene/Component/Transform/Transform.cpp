
#include "Transform.h"

namespace Volund
{
	void Transform::SetRotation(const Vec3& rotation)
	{
		this->quat = Quat(Math::Radians(rotation));
	}

	Vec3 Transform::GetRotation() const
	{
		return Math::Degress(this->quat.EulerAngles());
	}

	void Transform::AddRotation(const Vec3& rotation)
	{
		this->quat *= Quat(Math::Radians(rotation));
	}

	Vec3 Transform::GetFront() const
	{
		return this->quat * Math::BACK;
	}

	Vec3 Transform::GetRight() const
	{
		return this->quat * Math::RIGHT;
	}

	Vec3 Transform::GetUp() const
	{
		return this->quat * Math::UP;
	}

	Mat4x4 Transform::GetModelMatrix() const
	{
		Mat4x4 modelMatrix = Mat4x4(1.0f);

		modelMatrix = Math::Translate(modelMatrix, this->pos);
		modelMatrix *= Mat4x4(this->quat);
		modelMatrix = Math::scale(modelMatrix, this->scale);

		return modelMatrix;
	}

    Transform::Transform(Vec3 pos, Vec3 rotation, Vec3 scale)
	{
		this->pos = pos;
		this->quat = Quat(rotation);
		this->scale = scale;
	}
}
