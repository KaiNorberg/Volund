#include "PCH/PCH.h"

#include "Indexbuffer.h"

#include "OpenGLIndexbuffer.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	uint32_t Indexbuffer::GetCount() const
	{
		return this->_Count;
	}

	Ref<Indexbuffer> Indexbuffer::Create(uint32_t Indices[], uint32_t Size)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return std::make_shared<OpenGLIndexbuffer>(Indices, Size);
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
