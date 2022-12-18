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

		void BlitTo(const Ref<Framebuffer>& DrawFramebuffer) override;

		OpenGLFramebuffer(const FramebufferSpec& Spec);

		~OpenGLFramebuffer();

	private:
	};
}


