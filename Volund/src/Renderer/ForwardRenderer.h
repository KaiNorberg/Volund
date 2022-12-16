#pragma once

#include "Renderer.h"

namespace Volund
{
	class ForwardRenderer : public RendererInstance
	{
	public:

		void Begin() override;

		void Submit(const RendererCommand& Command) override;

		void Submit(const RendererLight& Light) override;

		void Submit(const RendererEye& Eye) override;

		void End() override;

		ForwardRenderer();

	private:		

	};
}

