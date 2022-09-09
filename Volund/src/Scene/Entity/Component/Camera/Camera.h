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

		static Camera* GetActiveCamera(Ref<Scene> ParentScene);

		Mat4x4 GetViewMatrix() const;

		Mat4x4 GetOriginViewMatrix() const;

		Mat4x4 GetProjectionMatrix(float AspectRatio) const;

		void OnCreate() override;

		void OnDelete() override;

		VML Serialize() override;

	private:
		static inline std::unordered_map<Scene*, Camera*> ActiveCameras = {};
	};
} //namespace Volund
