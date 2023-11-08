#pragma once

#include "Framebuffer.h"

namespace Volund
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:

		void Bind() override;

		void Unbind() override;

		void Invalidate() override;

		int32_t ReadPixel(uint32_t attachment, uint32_t x, uint32_t y) override;

		void BlitTo(const Ref<Framebuffer>& drawFramebuffer) override;

		void BlitToScreen() override;

		OpenGLFramebuffer(const FramebufferSpec& spec);

		~OpenGLFramebuffer();

	private:
	};
}


