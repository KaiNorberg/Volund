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

		uint32_t GetColorAttachment() override;

		OpenGLFramebuffer(const FramebufferSpec& Spec);

		~OpenGLFramebuffer();

	private:

		uint32_t _ID;

		uint32_t _ColorAttachment;		
		
		uint32_t _DepthAttachment;
	};
}


