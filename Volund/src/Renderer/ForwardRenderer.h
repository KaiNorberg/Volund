#pragma once

#include "Renderer.h"

namespace Volund
{
	class ForwardRenderer : public RendererInstance
	{
	public:

		void Begin(const Mat4x4& ViewMatrix, const Mat4x4& ProjectionMatrix) override;

		void Submit(const RendererCommand& Command) override;

		void Submit(const RendererLight& Light) override;

		void End() override;

		ForwardRenderer();

	private:		

	};
}

