#include "PCH/PCH.h"
#include "Framebuffer.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Volund
{
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_TEXTURE_2D, this->_ID);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_TEXTURE_2D, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		glCreateFramebuffers(1, &this->_ID);
		glBindFramebuffer(GL_TEXTURE_2D, this->_ID);

		glCreateTextures(GL_TEXTURE_2D, 1, &this->_ColorAttachment);		
		glBindTexture(GL_TEXTURE_2D, this->_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->_Spec.Width, this->_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_ColorAttachment, 0);
	
		glCreateTextures(GL_TEXTURE_2D, 1, &this->_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, this->_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->_Spec.Width, this->_Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->_DepthAttachment, 0);

		VOLUND_ASSERT(glCheckFramebufferStatus(this->_ID) == GL_FRAMEBUFFER_COMPLETE, "Error occurred while creating Framebuffer!");

		glBindFramebuffer(GL_TEXTURE_2D, 0);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachment()
	{
		return this->_ColorAttachment;
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& Spec)
	{
		this->_Spec = Spec;
		this->Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &this->_ID);
	}
}