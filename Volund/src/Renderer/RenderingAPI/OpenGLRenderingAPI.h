#pragma once

#include "RenderingAPI.h"
#include "Renderer/Mesh/Mesh.h"

#include "Renderer/Framebuffer/Framebuffer.h"

namespace Volund
{
	class OpenGLRenderingAPI : public RenderingAPIInstance
	{
	public:

		void SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height) override;

		void SetClearColor(const RGBA& Color) override;

		void Clear() override;

		void DrawIndexed(const Ref<Mesh>& VArray) override;

		OpenGLRenderingAPI();

	private:
	};
}
