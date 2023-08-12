#include "PCH/PCH.h"
#include "Framebuffer.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include "OpenGLFramebuffer.h"

namespace Volund
{
	uint32_t Framebuffer::GetID() const
	{
		return this->m_Id;
	}

	uint32_t Framebuffer::GetAttachment(const uint32_t index)
	{
		if (index >= this->m_ColorAttachments.size())
		{
			VOLUND_ERROR("Index out of range!");
			return 0;
		}
		else
		{
			return this->m_ColorAttachments[index];
		}
	}

	uint32_t Framebuffer::GetDepthAttachment()
	{
		return this->m_DepthAttachment;
	}

	void Framebuffer::SetSpec(const FramebufferSpec& spec)
	{
		this->m_Spec = spec;
		this->Invalidate();
	}

	const FramebufferSpec Framebuffer::GetSpec() const
	{
		return this->m_Spec;
	}

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLFramebuffer>(spec);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Framebuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}