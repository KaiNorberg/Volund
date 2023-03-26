#pragma once

#include "../Component.h"

namespace Volund
{
	class Transform : public Component
	{
	public:

		void SetRotation(const Vec3& rotation);
		Vec3 GetRotation() const;
		void AddRotation(const Vec3& rotation);

		Vec3 GetFront() const;
		Vec3 GetRight() const;
		Vec3 GetUp() const;

		Mat4x4 GetModelMatrix() const;

		Vec3 Position = Vec3(0.0f);

		Vec3 Scale = Vec3(1.0f);

		Quat Quaternion = Quat(Vec3(0.0f));

		Transform();

	private:

	};
}
