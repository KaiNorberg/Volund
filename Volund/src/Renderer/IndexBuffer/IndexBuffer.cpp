#include "PCH/PCH.h"

#include "Indexbuffer.h"

#include "OpenGLIndexbuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	uint32_t Indexbuffer::GetCount() const
	{
		return this->m_Count;
	}

	Ref<Indexbuffer> Indexbuffer::Create(const uint32_t indices[], uint32_t size)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLIndexbuffer>(indices, size);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Indexbuffer without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}
