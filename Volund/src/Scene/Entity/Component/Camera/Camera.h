#pragma once

#include "../Component.h"

namespace Volund
{
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
		
		void OnDelete() override;

		JSON Serialize() override;

	private:

		static inline Camera* ActiveCamera = nullptr;
	};

} //namespace Volund