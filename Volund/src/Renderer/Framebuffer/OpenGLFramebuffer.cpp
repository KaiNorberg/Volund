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

			for (int i = 0; i < this->_ColorAttachments.size(); i++)
			{
				glDeleteTextures(1, &this->_ColorAttachments[i]);
			}

			if (this->_DepthAttachment != NULL)
			{
				glDeleteTextures(1, &this->_DepthAttachment);
			}

			this->_ColorAttachments.clear();
			this->_DepthAttachment = NULL;
		}

		glGenFramebuffers(1, &this->_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, this->_ID);

		std::vector<GLenum> Buffers;
		for (int i = 0; i < this->_Spec.ColorAttachments.size(); i++)
		{
			uint32_t NewAttachment;

			glGenTextures(1, &NewAttachment);
			glBindTexture(GL_TEXTURE_2D, NewAttachment);

			switch (this->_Spec.ColorAttachments[i].Format)
			{
			case TextureFormat::RGBA8:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, this->_Spec.Width, this->_Spec.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			}
			break;
			case TextureFormat::RED_INTEGER:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, this->_Spec.Width, this->_Spec.Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);
			}
			break;
			default:
			{
				VOLUND_INFO("Unknown TextureFormat!");
			}
			break;
			}

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			VOLUND_INFO("%d", GL_COLOR_ATTACHMENT0 + i);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, NewAttachment, 0);

			Buffers.push_back(GL_COLOR_ATTACHMENT0 + i);

			this->_ColorAttachments.push_back(NewAttachment);
		}

		glDrawBuffers(this->_Spec.ColorAttachments.size(), Buffers.data());

		if (this->_Spec.DepthAttachment.Format != TextureFormat::NONE)
		{
			glGenTextures(1, &this->_DepthAttachment);
			glBindTexture(GL_TEXTURE_2D, this->_DepthAttachment);	

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			switch (this->_Spec.DepthAttachment.Format)
			{
			case TextureFormat::DEPTH24STENCIL8:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->_Spec.Width, this->_Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->_DepthAttachment, 0);
			}
			break;
			default:
			{
				VOLUND_INFO("Unknown TextureFormat!");
			}
			break;
			}
		}

		//VOLUND_ASSERT(glCheckFramebufferStatus(this->_ID) == GL_FRAMEBUFFER_COMPLETE, "Error occurred while creating Framebuffer!"); False positive?
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& Spec)
	{
		this->_Spec = Spec;
		this->Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (this->_ID != 0)
		{
			glDeleteFramebuffers(1, &this->_ID);

			for (int i = 0; i < this->_ColorAttachments.size(); i++)
			{
				glDeleteTextures(1, &this->_ColorAttachments[i]);
			}

			if (this->_DepthAttachment != NULL)
			{
				glDeleteTextures(1, &this->_DepthAttachment);
			}

			this->_ColorAttachments.clear();
			this->_DepthAttachment = NULL;
		}
	}
}