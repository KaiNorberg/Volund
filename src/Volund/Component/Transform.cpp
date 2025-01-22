
#include "Component/Transform.hpp"
#include "Lua/LuaAPI.hpp"

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
		modelMatrix = Math::Scale(modelMatrix, this->scale);

		return modelMatrix;
	}

    Transform::Transform(const Vec3& pos, const Vec3& rotation, const Vec3& scale)
	{
		this->pos = pos;
		this->quat = Quat(rotation);
		this->scale = scale;
	}

    VOLUND_USERTYPE_COMPONENT_REGISTER(Transform,
    [](LuaState* state){
        state->NewUsertype<Transform>("Transform", 
            sol::constructors<>(),
            "pos", &Transform::pos,
            "scale", &Transform::scale,
            "set_rotation", &Transform::SetRotation,
            "get_rotation", &Transform::GetRotation,
            "add_rotation", &Transform::AddRotation,
            "get_front", &Transform::GetFront,
            "get_right", &Transform::GetRight,
            "get_up", &Transform::GetUp,
            "get_model_matrix", &Transform::GetModelMatrix
        );
    }, const Vec3&, const Vec3&, const Vec3&);
}