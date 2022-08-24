#pragma once
#include "PCH/PCH.h"

#include "Shader.h"

namespace Volund
{
	Shader::Source Shader::ParseShader(std::string const& FilePath)
	{
		std::ifstream stream(FilePath);

		if (stream.fail())
		{
			VOLUND_CORE_INFO("Cant find shader: (%s).", FilePath.c_str());
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

		std::string line;
		std::stringstream ss[3];
		ShaderType type = ShaderType::NONE;

		while (std::getline(stream, line))
		{
			if (line.find("#Shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAGMENT;
				}
				else if (line.find("geometry") != std::string::npos)
				{
					type = ShaderType::GEOMETRY;
				}
			}
			else
			{
				if ((int32_t)type != -1)
				{
					if (line.find("#version FILL") != std::string::npos)
					{
						line = VersionString;
					}
					ss[(int32_t)type] << line << '\n';
				}
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