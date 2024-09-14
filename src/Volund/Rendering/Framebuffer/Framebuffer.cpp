#include "PCH/PCH.h"
#include "Framebuffer.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include "OpenGLFramebuffer.h"

namespace Volund
{
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec)
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
