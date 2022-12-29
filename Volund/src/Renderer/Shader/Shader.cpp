#pragma once
#include "PCH/PCH.h"

#include "Shader.h"

#include "Filesystem/Filesystem.h"

#include "OpenGLShader.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Ref<Shader> Shader::Create(const std::string& Filepath)
	{
		VOLUND_INFO("Loading Shader (%s)...", Filepath.c_str());

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAGMENT = 1,
			GEOMETRY = 2
		};

		std::string Line;
		std::stringstream SourceStrings[3];
		ShaderType Type = ShaderType::NONE;

		std::istringstream iss = std::istringstream(Filesystem::LoadFile(Filepath));
		while (std::getline(iss, Line))
		{
			//Split into words
			std::vector<std::string> Words;
			std::istringstream ISS(Line);
			std::copy(std::istream_iterator<std::string>(ISS), std::istream_iterator<std::string>(),
				std::back_inserter(Words));

			if (Words.size() <= 0)
			{
				continue;
			}

			if (Words.size() >= 2 && Words[0] == "#VOLUND_SHADER_TYPE")
			{
				if (Words[1] == "VERTEX")
				{
					Type = ShaderType::VERTEX;
				}
				else if (Words[1] == "FRAGMENT")
				{
					Type = ShaderType::FRAGMENT;
				}
				else if (Words[1] == "GEOMETRY")
				{
					Type = ShaderType::GEOMETRY;
				}
			}
			else if ((int32_t)Type != -1)
			{
				SourceStrings[(int32_t)Type] << Line << '\n';
			}
		}

		return Shader::Create(
			SourceStrings[(uint32_t)ShaderType::VERTEX].str(),
			SourceStrings[(uint32_t)ShaderType::FRAGMENT].str(),
			SourceStrings[(uint32_t)ShaderType::GEOMETRY].str());
	}

	Ref<Shader> Shader::Create(const std::string& VertexSource, const std::string& FragmentSource, const std::string& GeometrySource)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case GraphicsAPI::OPENGL:
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
