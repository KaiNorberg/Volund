#include "Rendering/Texture.h"

#include "Rendering/RenderingAPI.h"
#include "ImageLoader.h"

#include "Rendering/OpenGL/OpenGLTexture.h"

namespace Volund
{
	std::shared_ptr<Texture> Texture::Create(std::string const& filepath)
	{		
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLTexture>(filepath);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Texture without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}

	std::shared_ptr<Texture> Texture::Create(unsigned char* data, uint32_t width, uint32_t height)
	{		
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLTexture>(data, width, height);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Texture without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
}