#include "PCH/PCH.h"

#include "VertexBuffer.h"

#include "OpenGLVertexBuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#define BIT_MASK 0b1110000000111

namespace Volund
{
	VertexBuffer* VertexBuffer::Create(float Vertices[], uint32_t Count)
	{
		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
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