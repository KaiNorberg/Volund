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

	uint32_t Texture::GetWidth() const
	{
		return this->_Width;
	}

	uint32_t Texture::GetHeight() const
	{
		return this->_Height;
	}

	Ref<Texture> Texture::Create(const std::string& FilePath)
	{
		VOLUND_INFO("Loading Texture2D (%s)...", FilePath.c_str());

		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return std::make_shared<OpenGLTexture>(FilePath);
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
