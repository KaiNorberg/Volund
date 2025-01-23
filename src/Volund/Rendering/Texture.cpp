#include "Rendering/Texture.hpp"

#include "Rendering/RenderingAPI.hpp"
#include "ImageLoader.hpp"
#include "Rendering/OpenGL/OpenGLTexture.hpp"
#include "Lua/LuaAPI.hpp"

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
	
	VOLUND_USERTYPE_REGISTER(Texture,
    [](LuaState* state){
        state->NewUsertype<Texture>("Texture", 
            "new", sol::overload(
                [state](std::string const& filepath) { return Texture::Create(state->AbsolutePath(filepath)); },
                [](uint32_t width, uint32_t height, sol::table imageData) 
                {
                    std::vector<unsigned char> pixels;
                    for (auto& [key, value] : imageData) 
                    {
                        pixels.push_back(value.as<unsigned char>());
                    }

                    return Texture::Create(pixels.data(), width, height);
                }
            ),
            "get_id", &Texture::GetID,
            "get_width", &Texture::GetWidth,
            "get_height", &Texture::GetHeight,
            "bind", sol::overload(
                [](std::shared_ptr<Texture> texture) { texture->Bind(); },
                [](std::shared_ptr<Texture> texture, uint32_t unit) { texture->Bind(unit); }
            ),
            "set_data", [](std::shared_ptr<Texture> texture, uint32_t width, uint32_t height, sol::table imageData) 
            {
                std::vector<unsigned char> pixels;
                for (auto& [key, value] : imageData) 
                {
                    pixels.push_back(value.as<unsigned char>());
                }

                texture->SetData(pixels.data(), width, height);
            }
        );
    });
}