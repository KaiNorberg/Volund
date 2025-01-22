
#include "Rendering/VertexBuffer.hpp"

#include "Rendering/OpenGL/OpenGLVertexBuffer.hpp"

#include "Rendering/RenderingAPI.hpp"

#define BIT_MASK 0b1110000000111

namespace Volund
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(const float vertices[], uint64_t count)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLVertexBuffer>(vertices, count);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a VertexBuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}