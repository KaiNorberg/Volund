#pragma once

#include "RenderingAPI.h"
#include "Renderer/Mesh/Mesh.h"

#include "Renderer/Framebuffer/Framebuffer.h"

namespace Volund
{
	class OpenGLRenderingAPI : public RenderingAPIInstance
	{
	public:

		IVec2 GetViewSize() override;

		void SetViewPort(int32_t x, int32_t y, int32_t width, int32_t height) override;

		void Clear(const RGBA color) override;

		void DrawIndexed(const Ref<Mesh>& mesh) override;

		OpenGLRenderingAPI();

	private:
	};
}
