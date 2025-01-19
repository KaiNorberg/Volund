
#include "Rendering/IndexBuffer.h"

#include "Rendering/OpenGL/OpenGLIndexBuffer.h"

#include "Rendering/RenderingAPI.h"

namespace Volund
{
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t indices[], uint64_t count)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a IndexBuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}