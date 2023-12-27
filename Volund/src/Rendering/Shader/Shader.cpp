#include "PCH/PCH.h"

#include "Shader.h"

#include "OpenGLShader.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

namespace Volund
{
    Ref<Shader> Shader::Create()
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

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		Ref<ShaderLoader> loader = std::make_shared<ShaderLoader>(filepath);

		return Shader::Create(loader->GetSource(), loader->GetBlueprint());
	}

	Ref<Shader> Shader::Create(const ShaderSource& source, Ref<MaterialBlueprint> materialBlueprint)
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
