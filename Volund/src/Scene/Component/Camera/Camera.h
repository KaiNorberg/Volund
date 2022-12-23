#pragma once

#include "../Component.h"

namespace Volund
{
	class Scene;

	class Camera : public Component
	{
	public:

		float FOV = 80.0f;

		float NearPlane = 0.1f;

		float FarPlane = 100.0f;

		Mat4x4 GetViewMatrix() const;

		Mat4x4 GetOriginViewMatrix() const;

		Mat4x4 GetProjectionMatrix(float AspectRatio) const;

		void Procedure(const Event& E);

		Camera() = default;

	private:
	};
}
