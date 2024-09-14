#include "PCH/PCH.h"
#include "Texture.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"
#include "ImageLoader/ImageLoader.h"

#include "OpenGLTexture.h"

namespace Volund
{
	std::shared_ptr<Texture> Texture::Create()
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

	std::shared_ptr<Texture> Texture::Create(const std::string& filepath)
	{
		ImageLoader loader = ImageLoader(filepath);
		return Texture::Create(loader.GetData(), loader.GetWidth(), loader.GetHeight());
	}

	std::shared_ptr<Texture> Texture::Create(unsigned char* data, uint32_t width, uint32_t height)
	{
		auto texture = Texture::Create();
		texture->SetData(data, width, height);
		return texture;
	}
}
