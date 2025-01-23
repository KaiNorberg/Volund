#include "Rendering/UniformBufferBackend.hpp"

#include "Rendering/RenderingAPI.hpp"

#include "Rendering/OpenGL/OpenGLUniformBufferBackend.hpp"

namespace Volund
{
	std::shared_ptr<UniformBufferBackend> UniformBufferBackend::Create(uint32_t size, uint32_t binding)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLUniformBufferBackend>(size, binding);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a UniformBuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}

	UniformBufferBackend::~UniformBufferBackend()
	{
	}
}