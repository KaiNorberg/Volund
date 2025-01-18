
#include "Shader.h"

#include "OpenGLShader.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

namespace Volund
{
    std::shared_ptr<Shader> Shader::Create()
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLShader>();
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

	std::shared_ptr<Shader> Shader::Create(std::string const& filepath)
	{
		std::shared_ptr<ShaderLoader> loader = std::make_shared<ShaderLoader>(filepath);

		return Shader::Create(loader->GetSource(), loader->GetBlueprint());
	}

	std::shared_ptr<Shader> Shader::Create(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLShader>(source, materialBlueprint);
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
