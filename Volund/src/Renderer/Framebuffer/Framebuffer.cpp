#include "PCH/PCH.h"
#include "Framebuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLFramebuffer.h"

namespace Volund
{
	uint32_t Framebuffer::GetAttachment(uint32_t Index)
	{
		if (Index >= this->_ColorAttachments.size())
		{
			VOLUND_ERROR("Index out of range!");
			return 0;
		}
		else
		{
			return this->_ColorAttachments[Index];
		}
	}

	uint32_t Framebuffer::GetDepthAttachment()
	{
		return this->_DepthAttachment;
	}

	void Framebuffer::SetSpec(const FramebufferSpec& Spec)
	{
		this->_Spec = Spec;
	}

	const FramebufferSpec Framebuffer::GetSpec() const
	{
		return this->_Spec;
	}

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpec& Spec)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return std::make_shared<OpenGLFramebuffer>(Spec);
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