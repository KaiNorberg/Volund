#include "PCH/PCH.h"

#include "Vertexbuffer.h"

#include "OpenGLVertexbuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#define BIT_MASK 0b1110000000111

namespace Volund
{
	uint32_t Vertexbuffer::GetCount() const
	{
		return this->m_Count;
	}

	Ref<Vertexbuffer> Vertexbuffer::Create(const float vertices[], uint32_t count)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLVertexbuffer>(vertices, count);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Vertexbuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}
