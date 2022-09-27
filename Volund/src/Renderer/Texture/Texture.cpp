#include "PCH/PCH.h"
#include "Texture.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLTexture.h"

namespace Volund
{
	std::string Texture::GetFilepath()
	{
		return this->_Filepath;
	}

	uint32_t Texture::GetWidth() const
	{
		return this->_Width;
	}

	uint32_t Texture::GetHeight() const
	{
		return this->_Height;
	}

	Ref<Texture> Texture::Create(std::string_view Filepath)
	{
		VOLUND_INFO("Loading Texture2D (%s)...", Filepath.data());

		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			return std::make_shared<OpenGLTexture>(Filepath);
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
