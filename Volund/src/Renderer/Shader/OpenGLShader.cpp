#pragma once

#include "PCH/PCH.h"
#include "OpenGLShader.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	bool OpenGLShader::HasUniform(std::string_view Name)
	{
		return UniformLocations.contains(Name.data()) || glGetUniformLocation(this->ID, Name.data()) != -1;
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(this->ID);
	}

	void OpenGLShader::SetInt(std::string_view Name, int32_t Value)
	{
		this->Bind();
		glUniform1i(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetFloat(std::string_view Name, float Value)
	{
		this->Bind();
		glUniform1f(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetDouble(std::string_view Name, double Value)
	{
		this->Bind();
		glUniform1d(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetVec2(std::string_view Name, const Vec2& Value)
	{
		this->Bind();
		glUniform2fv(this->GetUniformLocation(Name), 1, value_ptr(Value));
	}

	void OpenGLShader::SetVec3(std::string_view Name, const Vec3& Value)
	{
		this->Bind();
		glUniform3fv(this->GetUniformLocation(Name), 1, value_ptr(Value));
	}

	void OpenGLShader::SetVec4(std::string_view Name, const Vec4& Value)
	{
		this->Bind();
		glUniform4fv(this->GetUniformLocation(Name), 1, value_ptr(Value));
	}

	void OpenGLShader::SetMat3x3(std::string_view Name, const Mat3x3& Value, bool Transpose)
	{
		this->Bind();
		glUniformMatrix3fv(this->GetUniformLocation(Name), 1, Transpose, value_ptr(Value));
	}

	void OpenGLShader::SetMat4x4(std::string_view Name, const Mat4x4& Value, bool Transpose)
	{
		this->Bind();
		glUniformMatrix4fv(this->GetUniformLocation(Name), 1, Transpose, value_ptr(Value));
	}

	uint32_t OpenGLShader::CompileShader(uint32_t type, std::string_view source)
	{
		uint32_t id = glCreateShader(type);
		const char* src = source.data();
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

	uint32_t OpenGLShader::GetUniformLocation(std::string_view Name)
	{
		if (UniformLocations.contains(Name.data()))
		{
			return UniformLocations[Name.data()];
		}
		int32_t UniformLocation = glGetUniformLocation(this->ID, Name.data());

		if (UniformLocation == -1)
		{
			VOLUND_WARNING("Unknown Uniform specified (%s)", Name.data());
		}

		UniformLocations[Name.data()] = UniformLocation;
		return UniformLocation;
	}

	OpenGLShader::OpenGLShader(std::string_view VertexSource, std::string_view FragmentSource, std::string_view GeometrySource)
	{
		uint32_t program = glCreateProgram();

		uint32_t vs = NULL;
		if (VertexSource.length() > 1)
		{
			vs = CompileShader(GL_VERTEX_SHADER, VertexSource.data());
			glAttachShader(program, vs);
		}

		uint32_t fs = NULL;
		if (FragmentSource.length() > 1)
		{
			fs = CompileShader(GL_FRAGMENT_SHADER, FragmentSource.data());
			glAttachShader(program, fs);
		}

		uint32_t gs = NULL;
		if (GeometrySource.length() > 1)
		{
			gs = CompileShader(GL_GEOMETRY_SHADER, GeometrySource.data());
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

	OpenGLShader::~OpenGLShader()
	{
		if (this->ID != 0)
		{
			glDeleteProgram(this->ID);
		}
	}
} //namespace Volund
