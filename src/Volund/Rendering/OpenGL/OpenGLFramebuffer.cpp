#include "Rendering/Framebuffer.h"
#include "Rendering/OpenGL/OpenGLFramebuffer.h"

#include "Rendering/RenderingAPI.h"
#include "Rendering/Uniform.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Volund
{
	uint32_t OpenGLFramebuffer::GetID() const
	{
		return this->m_id;
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (this->m_id != 0)
		{
			glDeleteFramebuffers(1, &this->m_id);

			for (int i = 0; i < this->m_colorAttachments.size(); i++)
			{
				glDeleteTextures(1, &this->m_colorAttachments[i]);
			}

			if (this->m_depthAttachment != 0)
			{
				glDeleteTextures(1, &this->m_depthAttachment);
			}

			this->m_colorAttachments.clear();
			this->m_depthAttachment = 0;
		}

		glGenFramebuffers(1, &this->m_id);
		glBindFramebuffer(GL_FRAMEBUFFER, this->m_id);

		for (int i = 0; i < this->m_spec.ColorAttachments.size(); i++)
		{
			uint32_t newAttachment;

			glGenTextures(1, &newAttachment);
			glBindTexture(GL_TEXTURE_2D, newAttachment);

			switch (this->m_spec.ColorAttachments[i].Format)
			{
			case TextureFormat::RGBA8:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_spec.Width, this->m_spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			}
			break;
			case TextureFormat::RGBA16F:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, this->m_spec.Width, this->m_spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
			}
			break;
			case TextureFormat::RGBA32UI:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, this->m_spec.Width, this->m_spec.Height, 0, GL_RGBA_INTEGER, GL_UNSIGNED_INT, nullptr);
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

			this->m_colorAttachments.push_back(newAttachment);
		}

		if (this->m_spec.DepthAttachment.Format != TextureFormat::None)
		{
			glGenTextures(1, &this->m_depthAttachment);
			glBindTexture(GL_TEXTURE_2D, this->m_depthAttachment);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			switch (this->m_spec.DepthAttachment.Format)
			{
			case TextureFormat::Depth24Stencil8:
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, this->m_spec.Width, this->m_spec.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, this->m_depthAttachment, 0);
			}
			break;
			default:
			{
				VOLUND_INFO("Unknown TextureFormat!");
			}
			break;
			}
		}

		VOLUND_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Error occurred while creating Framebuffer!");
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	/*int32_t OpenGLFramebuffer::ReadPixel(uint32_t attachment, uint32_t x, uint32_t y)
	{
		if (attachment < this->m_colorAttachments.size())
		{
			this->Bind();
			glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment);
			uint32_t pixel[4] = { 0, 0, 0, 0 };
			glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_INT, &pixel);

			VOLUND_INFO("%u, %u, %u, %u", pixel[0], pixel[1], pixel[2], pixel[3]);
			return 0;
		}
		else
		{
			return 0;
		}
	}*/

	void OpenGLFramebuffer::BlitTo(const std::shared_ptr<Framebuffer>& drawFramebuffer)
	{
		glBlitNamedFramebuffer(this->m_id, drawFramebuffer->GetID(),
			0, 0, this->m_spec.Width, this->m_spec.Height,
			0, 0, drawFramebuffer->GetSpec().Width, drawFramebuffer->GetSpec().Height,
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLFramebuffer::BlitToScreen()
	{
		auto context = glfwGetCurrentContext();

		int width, height;
		glfwGetWindowSize(context, &width, &height);

		glBlitNamedFramebuffer(this->m_id, 0,
			0, 0, this->m_spec.Width, this->m_spec.Height,
			0, 0, width, height,
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, GL_NEAREST);
	}

	uint32_t OpenGLFramebuffer::GetAttachment(const uint32_t index)
	{
		if (index >= this->m_colorAttachments.size())
		{
			VOLUND_ERROR("Index out of range!");
			return 0;
		}
		else
		{
			return this->m_colorAttachments[index];
		}
	}

	uint32_t OpenGLFramebuffer::GetDepthAttachment()
	{
		return this->m_depthAttachment;
	}

	void OpenGLFramebuffer::SetSpec(const FramebufferSpec& spec)
	{
		this->m_spec = spec;
		this->Invalidate();
	}

	const FramebufferSpec OpenGLFramebuffer::GetSpec() const
	{
		return this->m_spec;
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec)
	{
		this->m_spec = spec;
		this->Invalidate();

		this->Bind();
		RenderingAPI::Clear();
		this->Unbind();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		if (this->m_id != 0)
		{
			glDeleteFramebuffers(1, &this->m_id);

			for (int i = 0; i < this->m_colorAttachments.size(); i++)
			{
				glDeleteTextures(1, &this->m_colorAttachments[i]);
			}

			if (this->m_depthAttachment != 0)
			{
				glDeleteTextures(1, &this->m_depthAttachment);
			}

			this->m_colorAttachments.clear();
			this->m_depthAttachment = 0;
		}
	}
}