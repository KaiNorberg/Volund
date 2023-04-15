#include "PCH/PCH.h"

#include "Shader.h"

#include "Filesystem/Filesystem.h"

#include "OpenGLShader.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Ref<Shader> Shader::Create(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OpenGL:
		{
			return std::make_shared<OpenGLShader>(vertexSource, fragmentSource, geometrySource);
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
