#include "PCH/PCH.h"

#include "VertexBuffer.h"

#include "OpenGLVertexBuffer.h"

#include "Renderer/Renderer.h"

namespace Volund
{
	uint32_t VertexBuffer::GetCount()
	{
		return this->_Count;
	}

	VertexBuffer* VertexBuffer::Create(float Vertices[], uint32_t Count)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return new OpenGLVertexBuffer(Vertices, Count);
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