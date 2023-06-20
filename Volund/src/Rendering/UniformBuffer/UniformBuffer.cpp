#include "PCH/PCH.h"
#include "UniformBuffer.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include "OpenGLUniformBuffer.h"

namespace Volund
{
	Ref<UniformBuffer> UniformBuffer::Create(uint32_t size, uint32_t binding)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLUniformBuffer>(size, binding);
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

	UniformBuffer::~UniformBuffer()
	{
	}
}