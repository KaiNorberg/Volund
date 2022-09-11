#pragma once

#include "RenderingAPI.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:
		void SetViewPort(int32_t X, int32_t Y, int32_t Width, int32_t Height) override;

		void SetClearColor(const RGBA& Color) override;

		void Clear() override;

		void DrawIndexed(const Ref<Mesh>& VArray) override;

		void Init() override;

		OpenGLRenderingAPI();

	private:
	};
}
