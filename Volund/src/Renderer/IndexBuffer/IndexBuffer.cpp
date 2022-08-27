#include "PCH/PCH.h"

#include "IndexBuffer.h"

#include "OpenGLIndexBuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	uint32_t IndexBuffer::GetCount()
	{
		return this->_Count;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t Indices[], uint32_t Size)
	{
		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return new OpenGLIndexBuffer(Indices, Size);
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