#include "PCH/PCH.h"
#include "Texture.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLTexture.h"

namespace Volund
{
	std::string Texture::GetFilepath()
	{
		return this->m_Filepath;
	}

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

	Ref<Texture> Texture::Create(const std::string& filepath)
	{
		VOLUND_INFO("Loading Texture2D (%s)...", filepath.data());

		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLTexture>(filepath);
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
