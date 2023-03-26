#pragma once

#include "../Component.h"
#include "Renderer/Framebuffer/Framebuffer.h"

namespace Volund
{
	class Scene;

	class Camera : public Component
	{
	public:

		float FOV = 80.0f;

		float NearPlane = 0.1f;

		float FarPlane = 100.0f;

		void SetLayerMask(uint8_t index, bool enabled);

		void SetTargetBuffer(Ref<Framebuffer> newTargetBuffer);

		Mat4x4 GetViewMatrix() const;

		Mat4x4 GetOriginViewMatrix() const;

		Mat4x4 GetProjectionMatrix(float aspectRatio) const;

		void Procedure(const Event& e);

		void OnCreate() override;

		Camera() = default;

	private:

		uint16_t m_LayerMask = std::numeric_limits<uint16_t>::max();

		Ref<Framebuffer> m_TargetBuffer;
	};
}
