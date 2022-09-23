#include "PCH/PCH.h"
#include "Framebuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLFramebuffer.h"

namespace Volund
{
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
		case RenderingAPI::API::OPENGL:
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