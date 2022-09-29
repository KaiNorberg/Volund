#include "PCH/PCH.h"
#include "UniformBuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLUniformBuffer.h"

namespace Volund
{
	Ref<UniformBuffer> UniformBuffer::Create()
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return std::make_shared<OpenGLUniformBuffer>();
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