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

		void BlitTo(const Ref<Framebuffer>& drawFramebuffer) override;

		OpenGLFramebuffer(const FramebufferSpec& spec);

		~OpenGLFramebuffer();

	private:
	};
}


