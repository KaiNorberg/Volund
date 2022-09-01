#pragma once

#include "RenderingAPI.h"
#include "Renderer/Mesh/Mesh.h"

namespace Volund
{
	class OpenGLRenderingAPI : public RenderingAPI
	{
	public:

		void SetClearColor(RGBA const& Color) override;

		void Clear() override;

		void DrawIndexed(Ref<Mesh> const& VArray) override;

	private:
	};
}

