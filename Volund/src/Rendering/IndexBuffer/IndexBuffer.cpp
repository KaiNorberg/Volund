#include "PCH/PCH.h"

#include "IndexBuffer.h"

#include "OpenGLIndexBuffer.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	uint32_t IndexBuffer::GetCount() const
	{
		return this->m_Count;
	}

	Ref<IndexBuffer> IndexBuffer::Create(const uint32_t indices[], uint32_t size)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
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
