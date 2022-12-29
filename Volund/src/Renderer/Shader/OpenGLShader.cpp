#pragma once

#include "PCH/PCH.h"
#include "OpenGLShader.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	bool OpenGLShader::HasUniform(const std::string& Name)
	{
		VOLUND_PROFILE_FUNCTION();
		return UniformLocations.contains(Name.data()) || glGetUniformLocation(this->ID, Name.data()) != -1;
	}

	void OpenGLShader::Bind()
	{
		VOLUND_PROFILE_FUNCTION();
		glUseProgram(this->ID);
	}

	void OpenGLShader::SetInt(const std::string& Name, int32_t Value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1i(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetFloat(const std::string& Name, float Value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1f(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetDouble(const std::string& Name, double Value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1d(this->GetUniformLocation(Name), Value);
	}

	void OpenGLShader::SetVec2(const std::string& Name, const Vec2& Value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform2fv(this->GetUniformLocation(Name), 1, value_ptr(Value));
	}

	void OpenGLShader::SetVec3(const std::string& Name, const Vec3& Value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform3fv(this->GetUniformLocation(Name), 1, value_ptr(Value));
	}

	void OpenGLShader::SetVec4(const std::string& Name, const Vec4& Value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform4fv(this->GetUniformLocation(Name), 1, value_ptr(Value));
	}

	void OpenGLShader::SetMat3x3(const std::string& Name, const Mat3x3& Value, bool Transpose)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniformMatrix3fv(this->GetUniformLocation(Name), 1, Transpose, value_ptr(Value));
	}

	void OpenGLShader::SetMat4x4(const std::string& Name, const Mat4x4& Value, bool Transpose)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniformMatrix4fv(this->GetUniformLocation(Name), 1, Transpose, value_ptr(Value));
	}

	void OpenGLShader::SetTexture(const std::string& Name, const Ref<Texture>& Value, uint32_t TextureUnit)
	{
		VOLUND_PROFILE_FUNCTION();

		glActiveTexture(GL_TEXTURE0 + TextureUnit);
		glBindTexture(GL_TEXTURE_2D, Value->GetID());
		this->SetInt(Name, TextureUnit);
	}

	uint32_t OpenGLShader::CompileShader(uint32_t type, const std::string& source)
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

	uint32_t OpenGLShader::GetUniformLocation(const std::string& Name)
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

	OpenGLShader::OpenGLShader(const std::string& VertexSource, const std::string& FragmentSource, const std::string& GeometrySource)
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
