#include "PCH/PCH.h"

#include "VertexBuffer.h"

#include "OpenGLVertexBuffer.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#define BIT_MASK 0b1110000000111

namespace Volund
{
	AABB VertexBuffer::GetAABB()
	{
		return this->m_AABB;
	}

	Ref<VertexBuffer> VertexBuffer::Create(const float vertices[], uint32_t count)
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
