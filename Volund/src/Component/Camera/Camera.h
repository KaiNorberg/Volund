#pragma once

#include "Component/Component.h"

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

		Mat4x4 GetProjectionMatrix() const;

		void OnCreate() override;

		void OnEvent(Event* E) override;

		void OnUpdate(TimeStep TS) override;
		
		void OnDelete() override;

		JSON Serialize() override;

	private:

		static inline Camera* ActiveCamera = nullptr;

		void UpdateMatrices();

		float AspectRatio = 1.0f;

		Mat4x4 _ViewMatrix = Mat4x4(1.0f);

		Mat4x4 _OriginViewMatrix = Mat4x4(1.0f);

		Mat4x4 _ProjectionMatrix = Mat4x4(1.0f);
	};

} //namespace Volund