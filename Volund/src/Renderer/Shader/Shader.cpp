#pragma once
#include "PCH/PCH.h"

#include "Shader.h"
#include "OpenGLShader.h"

#include "Time/Time.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Ref<Shader> Shader::Create(std::string const& FilePath)
	{
		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return Ref<Shader>(new OpenGLShader(FilePath));
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

	Shader::Source Shader::ParseShader(std::string const& FilePath)
	{
		std::ifstream File(FilePath);

		if (File.fail())
		{
			VOLUND_INFO("Cant find Shader: (%s).", FilePath.c_str());
			return Source{};
		}

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
		};

		std::string Line;
		std::stringstream SourceStrings[3];
		ShaderType Type = ShaderType::NONE;

		while (std::getline(File, Line))
		{
			//Split into words
			std::vector<std::string> Words;
			std::istringstream ISS(Line);
			std::copy(std::istream_iterator<std::string>(ISS), std::istream_iterator<std::string>(), std::back_inserter(Words));

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

		return Source{ SourceStrings[(int)ShaderType::VERTEX].str(), SourceStrings[(int)ShaderType::FRAGMENT].str(), SourceStrings[(int)ShaderType::GEOMETRY].str()};
	}	
	
} //namespace Volund