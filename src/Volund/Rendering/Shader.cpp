
#include "Rendering/Shader.h"

#include "Rendering/OpenGL/OpenGLShader.h"

#include "Rendering/RenderingAPI.h"

namespace Volund
{
	std::shared_ptr<Shader> Shader::Create(std::string const& filepath)
	{		
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLShader>(filepath);
		}
		break;
		default:
		{
			VOLUND_ERROR("Creating a Shader without a specified GraphicsAPI!");
			return nullptr;
		}
		break;
		}
	}
} //namespace Volund