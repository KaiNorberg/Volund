#pragma once

#include "../Component.h"

namespace Volund
{
	class Scene;

	class Camera : public Component
	{
	public:

		float FOV = 70.0f;

		float NearPlane = 0.1f;

		float FarPlane = 100.0f;

		bool IsActive() const;

		void SetActive();

		static Camera* GetActiveCamera();

		Mat4x4 GetViewMatrix() const;

		Mat4x4 GetOriginViewMatrix() const;

		Mat4x4 GetProjectionMatrix(float AspectRatio) const;

		void OnCreate() override;

		void OnDelete() override;

		Camera() = default;

	private:

		static inline Camera* _ActiveCamera = nullptr;
	};
}
