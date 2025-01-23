#include "Rendering/Framebuffer.hpp"

#include "Rendering/RenderingAPI.hpp"

#include "Rendering/OpenGL/OpenGLFramebuffer.hpp"

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