#include "PCH/PCH.h"

#include "VertexBuffer.h"

#include "OpenGLVertexBuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#define BIT_MASK 0b1110000000111

namespace Volund
{
	uint32_t VertexBuffer::GetCount() const
	{
		return this->_Count;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float Vertices[], uint32_t Count)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
			{
				return std::make_shared<OpenGLVertexBuffer>(Vertices, Count);
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
