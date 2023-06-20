#pragma once

#include "../Renderer.h"

#define VOLUND_FORWARD_RENDERER_BINDING_CAMERA 0
#define VOLUND_FORWARD_RENDERER_BINDING_LIGHTS 1
#define VOLUND_FORWARD_RENDERER_MAX_LIGHTS 64

namespace Volund
{
	class ForwardRenderer : public Renderer
	{
	public:

		void Begin(Ref<Framebuffer> targetBuffer) override;

		void End() override;

		ForwardRenderer();

	private:	

		struct alignas(16) LightsBuffer
		{
			int LightAmount;

			char Padding1[sizeof(Vec4) - sizeof(int)];

			Vec4 LightColors[VOLUND_FORWARD_RENDERER_MAX_LIGHTS];
			Vec4 LightPositions[VOLUND_FORWARD_RENDERER_MAX_LIGHTS];
		};

		struct alignas(16) CameraBuffer
		{
			Mat4x4 ViewMatrix = Mat4x4();
			Mat4x4 ProjectionMatrix = Mat4x4();
		};

		Ref<UniformBuffer> m_CameraUniformBuffer;
		Ref<UniformBuffer> m_LightsUniformBuffer;
	};
}

