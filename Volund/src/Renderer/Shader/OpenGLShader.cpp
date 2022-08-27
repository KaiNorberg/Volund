#pragma once

#include "PCH/PCH.h"
#include "OpenGLShader.h"

namespace Volund
{
	void OpenGLShader::Init(std::string const& FilePath)
	{
		if (this->ID != NULL)
		{
			VOLUND_INFO("Shader (%s) already initialized.", FilePath.c_str());
			return;
		}
		VOLUND_INFO("Loading shader (%s)...", FilePath.c_str());

		Source Source = this->ParseShader(FilePath);

		uint32_t program = glCreateProgram();

		uint32_t vs = NULL;
		if (Source.VertexSource.length() > 1)
		{
			vs = CompileShader(GL_VERTEX_SHADER, Source.VertexSource);
			glAttachShader(program, vs);
		}

		uint32_t fs = NULL;
		if (Source.FragmentSource.length() > 1)
		{
			fs = CompileShader(GL_FRAGMENT_SHADER, Source.FragmentSource);
			glAttachShader(program, fs);
		}

		uint32_t gs = NULL;
		if (Source.GeometrySource.length() > 1)
		{
			gs = CompileShader(GL_GEOMETRY_SHADER, Source.GeometrySource);
			glAttachShader(program, gs);
		}

		glLinkProgram(program);
		glValidateProgram(program);

		if (vs != NULL)
		{
			glDeleteShader(vs);
		}

		if (fs != NULL)
		{
			glDeleteShader(fs);
		}

		if (gs != NULL)
		{
			glDeleteShader(gs);
		}

		this->ID = program;
	}

	void OpenGLShader::Use()
	{
		glUseProgram(this->ID);
	}

	void OpenGLShader::SetInt(int32_t Value, std::string const& Name)
	{
		this->Use();
		glUniform1i(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetFloat(float Value, std::string const& Name)
	{
		this->Use();
		glUniform1f(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetDouble(float Value, std::string const& Name)
	{
		this->Use();
		glUniform1d(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetVec2(Vec2 const& Value, std::string const& Name)
	{
		this->Use();
		glUniform2fv(this->GetUniformLocation(Name), 1, glm::value_ptr(Value));
	}

	void OpenGLShader::SetVec3(Vec3 const& Value, std::string const& Name)
	{
		this->Use();
		glUniform3fv(this->GetUniformLocation(Name), 1, glm::value_ptr(Value));
	}

	void OpenGLShader::SetVec4(Vec4 const& Value, std::string const& Name)
	{
		this->Use();
		glUniform4fv(this->GetUniformLocation(Name), 1, glm::value_ptr(Value));
	}

	void OpenGLShader::SetMat3x3(Mat3x3 const& Value, std::string const& Name, bool Transpose)
	{
		this->Use();
		glUniformMatrix3fv(this->GetUniformLocation(Name), 1, Transpose, glm::value_ptr(Value));
	}

	void OpenGLShader::SetMat4x4(Mat4x4 const& Value, std::string const& Name, bool Transpose)
	{
		this->Use();
		glUniformMatrix4fv(this->GetUniformLocation(Name), 1, Transpose, glm::value_ptr(Value));
	}

	uint32_t OpenGLShader::CompileShader(uint32_t type, std::string const& source)
	{
		uint32_t id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int32_t result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			int32_t length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * (sizeof(char)));
			glGetShaderInfoLog(id, length, &length, message);
			VOLUND_WARNING("Failed to compile shader: %s", message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	OpenGLShader::OpenGLShader(std::string const& FilePath)
	{
		this->Init(FilePath);
	}

	OpenGLShader::~OpenGLShader()
	{
		if (this->ID != 0)
		{
			glDeleteProgram(this->ID);
		}
	}

} //namespace Volund