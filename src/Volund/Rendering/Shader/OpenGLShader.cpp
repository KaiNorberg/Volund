#include "PCH/PCH.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Volund
{
	bool OpenGLShader::HasUniform(const std::string& name)
	{
		VOLUND_PROFILE_FUNCTION();
		return m_UniformLocations.contains(name.data()) || glGetUniformLocation(this->m_Id, name.data()) != -1;
	}

	void OpenGLShader::Bind()
	{
		VOLUND_PROFILE_FUNCTION();
		glUseProgram(this->m_Id);
	}

	uint32_t OpenGLShader::GetId()
	{
		return this->m_Id;
	}

	void OpenGLShader::SetInt(const std::string& name, IntUniformType value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1i(this->GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat(const std::string& name, FloatUniformType value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1f(this->GetUniformLocation(name), value);
	}

	void OpenGLShader::SetDouble(const std::string& name, DoubleUniformType value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1d(this->GetUniformLocation(name), value);
	}

	void OpenGLShader::SetVec2(const std::string& name, const Vec2UniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform2fv(this->GetUniformLocation(name), 1, &(value.x));
	}

	void OpenGLShader::SetVec3(const std::string& name, const Vec3UniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform3fv(this->GetUniformLocation(name), 1, &(value.x));
	}

	void OpenGLShader::SetVec4(const std::string& name, const Vec4UniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform4fv(this->GetUniformLocation(name), 1, &(value.x));
	}

	/*void OpenGLShader::SetMat3x3(const std::string& name, const UniformMat3x3& value, bool transpose)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniformMatrix3fv(this->GetUniformLocation(name), 1, transpose, value_ptr(value));
	}*/

	void OpenGLShader::SetMat4x4(const std::string& name, const Mat4x4UniformType& value, bool transpose)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniformMatrix4fv(this->GetUniformLocation(name), 1, transpose, &(value[0][0]));
	}

	void OpenGLShader::SetTexture(const std::string& name, const TextureUniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_NextTextureUnit >= this->m_MaxTextureUnit)
		{
			this->m_NextTextureUnit = 0;
		}

		glActiveTexture(GL_TEXTURE0 + this->m_NextTextureUnit);
		glBindTexture(GL_TEXTURE_2D, value->GetID());
		this->SetInt(name, this->m_NextTextureUnit);

		this->m_NextTextureUnit++;
	}

	void OpenGLShader::SetFramebuffer(const std::string& name, const FramebufferUniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_NextTextureUnit >= this->m_MaxTextureUnit)
		{
			this->m_NextTextureUnit = 0;
		}

		glActiveTexture(GL_TEXTURE0 + this->m_NextTextureUnit);
		glBindTexture(GL_TEXTURE_2D, value->GetAttachment(0));
		this->SetInt(name, this->m_NextTextureUnit);

		this->m_NextTextureUnit++;
	}

	void OpenGLShader::Init(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint)
	{
		this->m_MaterialBlueprint = materialBlueprint;

		uint32_t program = glCreateProgram();

		uint32_t vs = 0;
		if (source[(int)ShaderSourceType::Vertex].length() > 1)
		{
			vs = CompileShader(GL_VERTEX_SHADER, source[(int)ShaderSourceType::Vertex].data());
			glAttachShader(program, vs);
		}

		uint32_t fs = 0;
		if (source[(int)ShaderSourceType::Fragment].length() > 1)
		{
			fs = CompileShader(GL_FRAGMENT_SHADER, source[(int)ShaderSourceType::Fragment].data());
			glAttachShader(program, fs);
		}

		uint32_t gs = 0;
		if (source[(int)ShaderSourceType::Geometry].length() > 1)
		{
			gs = CompileShader(GL_GEOMETRY_SHADER, source[(int)ShaderSourceType::Geometry].data());
			glAttachShader(program, gs);
		}

		glLinkProgram(program);
		glValidateProgram(program);

		if (vs != 0)
		{
			glDeleteShader(vs);
		}

		if (fs != 0)
		{
			glDeleteShader(fs);
		}

		if (gs != 0)
		{
			glDeleteShader(gs);
		}

		this->m_Id = program;
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
			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			VOLUND_WARNING("Failed to compile shader: %s", message);
			delete message;
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	uint32_t OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocations.contains(name.data()))
		{
			return m_UniformLocations[name.data()];
		}
		int32_t uniformLocation = glGetUniformLocation(this->m_Id, name.data());

		if (uniformLocation == -1)
		{
			VOLUND_WARNING("Unknown Uniform specified (%s)", name.data());
		}

		m_UniformLocations[name.data()] = uniformLocation;
		return uniformLocation;
	}

	const std::shared_ptr<MaterialBlueprint> OpenGLShader::GetMaterialBlueprint()
	{
		return this->m_MaterialBlueprint;
	}

	OpenGLShader::OpenGLShader(const ShaderSource& source, std::shared_ptr<MaterialBlueprint> materialBlueprint)
	{
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->m_MaxTextureUnit);

		this->Init(source, materialBlueprint);
	}

	OpenGLShader::~OpenGLShader()
	{
		if (this->m_Id != 0)
		{
			glDeleteProgram(this->m_Id);
		}
	}
} //namespace Volund
