#include "PCH/PCH.h"
#include "Texture.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLTexture.h"

namespace Volund
{
	uint32_t Texture::GetID() const
	{
		return this->m_ID;
	}

	uint32_t Texture::GetWidth() const
	{
		return this->m_Width;
	}

	uint32_t Texture::GetHeight() const
	{
		return this->m_Height;
	}

	Ref<Texture> Texture::Create()
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLTexture>();
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Texture2D without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}
