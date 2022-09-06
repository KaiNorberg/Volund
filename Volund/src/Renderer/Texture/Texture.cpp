#include "PCH/PCH.h"
#include "Texture.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include "OpenGLTexture.h"

namespace Volund
{
	std::string Texture::GetFilePath()
	{
		return this->_FilePath;
	}

	uint32_t Texture::GetWidth()
	{
		return this->_Width;
	}

	uint32_t Texture::GetHeight()
	{
		return this->_Height;
	}

	Ref<Texture> Texture::Create(std::string const& FilePath)
	{
		VOLUND_INFO("Loading Texture2D (%s)...", FilePath.c_str());

		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return Ref<Texture>(new OpenGLTexture(FilePath));
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