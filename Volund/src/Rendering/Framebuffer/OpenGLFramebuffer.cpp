#include "PCH/PCH.h"
#include "Framebuffer.h"
#include "OpenGLFramebuffer.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_Id);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (this->m_Id != 0)
		{
			glDeleteFramebuffers(1, &this->m_Id);

			for (int i = 0; i < this->m_ColorAttachments.size(); i++)
			{
				glDeleteTextures(1, &this->m_ColorAttachments[i]);
			}

			if (this->m_DepthAttachment != 0)
			{
				glDeleteTextures(1, &this->m_DepthAttachment);
			}

			this->m_ColorAttachments.clear();
			this->m_DepthAttachment = 0;
		}

		glGenFramebuffers(1, &this->m_Id);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_Id);

		std::vector<GLenum> buffers;
		for (int i = 0; i < this->m_Spec.ColorAttachments.size(); i++)
		{
			uint32_t newAttachment;

			glGenTextures(1, &newAttachment);
			glBindTexture(GL_TEXTURE_2D, newAttachment);

			switch (this->m_Spec.ColorAttachments[i].Format)
			{
			case TextureFormat::RGBA8:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_Spec.Width, this->m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			}
			break;
			case TextureFormat::RGBA16F:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->m_Spec.Width, this->m_Spec.Height, 0, GL_RGBA, GL_FLOAT, nullptr);
			}
			break;
			case TextureFormat::RedInteger:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, this->m_Spec.Width, this->m_Spec.Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);
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

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, newAttachment, 0);

			buffers.push_back(GL_COLOR_ATTACHMENT0 + i);

			this->m_ColorAttachments.push_back(newAttachment);
		}

		glDrawBuffers(this->m_Spec.ColorAttachments.size(), buffers.data());

		if (this->m_Spec.DepthAttachment.Format != TextureFormat::None)
		{
			glGenTextures(1, &this->m_DepthAttachment);
			glBindTexture(GL_TEXTURE_2D, this->m_DepthAttachment);	

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			switch (this->m_Spec.DepthAttachment.Format)
			{
			case TextureFormat::Depth24Stencil8:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->m_Spec.Width, this->m_Spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_DepthAttachment, 0);
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

	void OpenGLFramebuffer::BlitTo(const Ref<Framebuffer>& drawFramebuffer)
	{
		glBlitNamedFramebuffer(this->m_Id, drawFramebuffer->GetID(),
			0, 0, this->m_Spec.Width, this->m_Spec.Height,
			0, 0, drawFramebuffer->GetSpec().Width, drawFramebuffer->GetSpec().Height,
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec)
	{
		this->m_Spec = spec;
		this->Invalidate();

		this->Bind();
		RenderingAPI::Clear();
		this->Unbind();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (this->m_Id != 0)
		{
			glDeleteFramebuffers(1, &this->m_Id);

			for (int i = 0; i < this->m_ColorAttachments.size(); i++)
			{
				glDeleteTextures(1, &this->m_ColorAttachments[i]);
			}

			if (this->m_DepthAttachment != 0)
			{
				glDeleteTextures(1, &this->m_DepthAttachment);
			}

			this->m_ColorAttachments.clear();
			this->m_DepthAttachment = 0;
		}
	}
}