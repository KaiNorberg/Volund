#include "PCH/PCH.h"

#include "IndexBuffer.h"

#include "OpenGLIndexBuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	uint32_t IndexBuffer::GetCount() const
	{
		return this->_Count;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t Indices[], uint32_t Size)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return std::make_shared<OpenGLIndexBuffer>(Indices, Size);
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
