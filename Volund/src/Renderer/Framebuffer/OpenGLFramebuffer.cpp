#include "PCH/PCH.h"
#include "Framebuffer.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Volund
{
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->_ID);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (this->_ID != 0)
		{
			glDeleteFramebuffers(1, &this->_ID);
			glDeleteTextures(1, &this->_ColorAttachment);
			glDeleteTextures(1, &this->_DepthAttachment);
		}

		glGenFramebuffers(1, &this->_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, this->_ID);

		glGenTextures(1, &this->_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, this->_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->_Spec.Width, this->_Spec.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->_ColorAttachment, 0);
	
		glGenTextures(1, &this->_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, this->_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->_Spec.Width, this->_Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->_DepthAttachment, 0);

		//VOLUND_ASSERT(glCheckFramebufferStatus(this->_ID) == GL_FRAMEBUFFER_COMPLETE, "Error occurred while creating Framebuffer!"); False positive?

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
		glDeleteTextures(1, &this->_ColorAttachment);
		glDeleteTextures(1, &this->_DepthAttachment);
	}
}