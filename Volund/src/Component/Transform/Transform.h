#pragma once

#include "Component/Component.h"

namespace Volund
{
	class Transform : public Component
	{
	public:

		void SetRotation(Vec3 const& Rotation);

		Vec3 GetRotation() const;

		void AddRotation(Vec3 const& Rotation);

		Vec3 GetFront();

		Vec3 GetRight();

		Vec3 GetUp();

		Mat4x4 GetModelMatrix();

		Vec3 Position = Vec3(0.0f);

		Vec3 Scale = Vec3(1.0f);

		Quat Quaternion = Quat(Vec3(0.0f));

		void OnUpdate(TimeStep TS) override;

		JSON Serialize() override;

		Transform(Vec3 const& Position = Vec3(0.0f), Vec3 const& Rotation = Vec3(0.0f), Vec3 const& Scale = Vec3(1.0f));

	private:

		Mat4x4 _ModelMatrix = Mat4x4(1.0f);

		Vec3 _Front = Vec3(0.0f);

		Vec3 _Right = Vec3(0.0f);

		Vec3 _Up = Vec3(0.0f);
	};
}

