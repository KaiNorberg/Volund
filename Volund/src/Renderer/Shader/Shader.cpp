#pragma once
#include "PCH/PCH.h"

#include "Shader.h"
#include "OpenGLShader.h"

#include "Time/Time.h"
#include "Renderer/RenderingAPI/RenderingAPI.h"

namespace Volund
{
	Shader* Shader::Create(std::string const& FilePath)
	{
		switch (RenderingAPI::GetAPI())
		{
		case RenderingAPI::API::OPENGL:
		{
			return new OpenGLShader(FilePath);
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
		std::ifstream stream(FilePath);

		if (stream.fail())
		{
			VOLUND_INFO("Cant find shader: (%s).", FilePath.c_str());
			return Source{};
		}

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
		};

		int MajorVersion, MinorVersion = NULL;
		glGetIntegerv(GL_MAJOR_VERSION, &MajorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &MinorVersion);

		std::string VersionString = "#version " + std::to_string(MajorVersion) + std::to_string(MinorVersion) + "0";

		std::string Line;
		std::stringstream ss[3];
		ShaderType Type = ShaderType::NONE;

		while (std::getline(stream, Line))
		{
			if (Line.find("#VOLUND_SHADER_TYPE") != std::string::npos)
			{
				if (Line.find("VERTEX") != std::string::npos)
				{
					Type = ShaderType::VERTEX;
				}
				else if (Line.find("FRAGMENT") != std::string::npos)
				{
					Type = ShaderType::FRAGMENT;
				}
				else if (Line.find("GEOMETRY") != std::string::npos)
				{
					Type = ShaderType::GEOMETRY;
				}
			}
			else if (Line.find("#VOLUND_SHADER_VERSION") != std::string::npos)
			{
				ss[(int32_t)Type] << VersionString << '\n';
			}
			else if ((int32_t)Type != -1)
			{
				ss[(int32_t)Type] << Line << '\n';
			}
		}

		return Source{ ss[(int)ShaderType::VERTEX].str(), ss[(int)ShaderType::FRAGMENT].str(), ss[(int)ShaderType::GEOMETRY].str() };
	}	
	
	uint32_t Shader::GetUniformLocation(std::string const& Name)
	{
		if (UniformLocations.find(Name) != UniformLocations.end())
		{
			return UniformLocations[Name];
		}

		uint32_t Location = glGetUniformLocation(this->ID, Name.c_str());

		if (Location == -1)
		{
			//Console::LogWarning("OpenGLShader (" + this->FilePath + ") does not have uniform (" + Name + ").");
			return -1;
		}

		UniformLocations[Name] = Location;

		return Location;
	}
} //namespace Volund