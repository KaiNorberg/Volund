#include "PCH/PCH.h"

#include "Vertexbuffer.h"

#include "OpenGLVertexbuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#define BIT_MASK 0b1110000000111

namespace Volund
{
	uint32_t Vertexbuffer::GetCount() const
	{
		return this->_Count;
	}

	Ref<Vertexbuffer> Vertexbuffer::Create(float Vertices[], uint32_t Count)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return std::make_shared<OpenGLVertexbuffer>(Vertices, Count);
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
