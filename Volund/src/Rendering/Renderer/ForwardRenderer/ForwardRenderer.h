#pragma once

#include "../Renderer.h"

namespace Volund
{
	class ForwardRenderer : public Renderer
	{
	public:

		void Begin(Ref<Framebuffer> defaultBuffer) override;

		void End() override;

	private:		

	};
}

