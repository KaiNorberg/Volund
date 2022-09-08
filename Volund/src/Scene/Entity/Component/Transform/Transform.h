#pragma once

#include "../Component.h"

namespace Volund
{
	class Transform : public Component
	{
	public:
		void SetRotation(const Vec3& Rotation);

		Vec3 GetRotation() const;

		void AddRotation(const Vec3& Rotation);

		Vec3 GetFront() const;

		Vec3 GetRight() const;

		Vec3 GetUp() const;

		Mat4x4 GetModelMatrix() const;

		Vec3 Position = Vec3(0.0f);

		Vec3 Scale = Vec3(1.0f);

		Quat Quaternion = Quat(Vec3(0.0f));

		void OnUpdate(TimeStep TS) override;

		JSON Serialize() override;

		Transform(const Vec3& Position = Vec3(0.0f), const Vec3& Rotation = Vec3(0.0f), const Vec3& Scale = Vec3(1.0f));

	private:
		Mat4x4 _ModelMatrix = Mat4x4(1.0f);

		Vec3 _Front = Vec3(0.0f);

		Vec3 _Right = Vec3(0.0f);

		Vec3 _Up = Vec3(0.0f);
	};
}
