#pragma once

#include "RenderingAPI.h"
#include "Renderer/VertexArray/VertexArray.h"

namespace Volund
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:

		void SetClearColor(RGBA const& Color) override;

		void Clear() override;

		void DrawIndexed(Ref<VertexArray> const& VArray) override;

	private:
	};
}

