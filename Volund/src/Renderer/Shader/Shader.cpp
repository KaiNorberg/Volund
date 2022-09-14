#pragma once
#include "PCH/PCH.h"

#include "Shader.h"
#include "OpenGLShader.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Ref<Shader> Shader::Create(std::string_view VertexSource, std::string_view FragmentSource, std::string_view GeometrySource)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return std::make_shared<OpenGLShader>(VertexSource, FragmentSource, GeometrySource);
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
