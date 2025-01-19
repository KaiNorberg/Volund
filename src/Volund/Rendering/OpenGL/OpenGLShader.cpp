#include "Rendering/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

#include "Instrumentor.h"

namespace Volund
{
	bool OpenGLShader::HasUniform(std::string const& name)
	{
		VOLUND_PROFILE_FUNCTION();
		return m_uniformLocations.contains(name.data()) || glGetUniformLocation(this->m_id, name.data()) != -1;
	}

	void OpenGLShader::Bind()
	{
		VOLUND_PROFILE_FUNCTION();
		glUseProgram(this->m_id);
	}

	uint32_t OpenGLShader::GetId() const
	{
		return this->m_id;
	}

	void OpenGLShader::SetInt(std::string const& name, IntUniformType value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1i(this->GetUniformLocation(name), value);
	}

	void OpenGLShader::SetFloat(std::string const& name, FloatUniformType value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1f(this->GetUniformLocation(name), value);
	}

	void OpenGLShader::SetDouble(std::string const& name, DoubleUniformType value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform1d(this->GetUniformLocation(name), value);
	}

	void OpenGLShader::SetVec2(std::string const& name, const Vec2UniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform2fv(this->GetUniformLocation(name), 1, &(value.x));
	}

	void OpenGLShader::SetVec3(std::string const& name, const Vec3UniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform3fv(this->GetUniformLocation(name), 1, &(value.x));
	}

	void OpenGLShader::SetVec4(std::string const& name, const Vec4UniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniform4fv(this->GetUniformLocation(name), 1, &(value.x));
	}

	/*void OpenGLShader::SetMat3x3(std::string const& name, const UniformMat3x3& value, bool transpose)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniformMatrix3fv(this->GetUniformLocation(name), 1, transpose, value_ptr(value));
	}*/

	void OpenGLShader::SetMat4x4(std::string const& name, const Mat4x4UniformType& value, bool transpose)
	{
		VOLUND_PROFILE_FUNCTION();

		this->Bind();
		glUniformMatrix4fv(this->GetUniformLocation(name), 1, transpose, &(value[0][0]));
	}

	void OpenGLShader::SetTexture(std::string const& name, const TextureUniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_nextTextureUnit >= this->m_maxTextureUnit)
		{
			this->m_nextTextureUnit = 0;
		}

		glActiveTexture(GL_TEXTURE0 + this->m_nextTextureUnit);
		glBindTexture(GL_TEXTURE_2D, value->GetID());
		this->SetInt(name, this->m_nextTextureUnit);

		this->m_nextTextureUnit++;
	}

	void OpenGLShader::SetFramebuffer(std::string const& name, const FramebufferUniformType& value)
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_nextTextureUnit >= this->m_maxTextureUnit)
		{
			this->m_nextTextureUnit = 0;
		}

		glActiveTexture(GL_TEXTURE0 + this->m_nextTextureUnit);
		glBindTexture(GL_TEXTURE_2D, value->GetAttachment(0));
		this->SetInt(name, this->m_nextTextureUnit);

		this->m_nextTextureUnit++;
	}

	uint32_t OpenGLShader::CompileShader(uint32_t type, std::string const& source)
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

	uint32_t OpenGLShader::GetUniformLocation(std::string const& name)
	{
		if (m_uniformLocations.contains(name.data()))
		{
			return m_uniformLocations[name.data()];
		}
		int32_t uniformLocation = glGetUniformLocation(this->m_id, name.data());

		if (uniformLocation == -1)
		{
			VOLUND_WARNING("Unknown Uniform specified (%s)", name.data());
		}

		m_uniformLocations[name.data()] = uniformLocation;
		return uniformLocation;
	}

	const std::shared_ptr<MaterialBlueprint> OpenGLShader::GetMaterialBlueprint() const
	{
		return this->m_materialBlueprint;
	}

	std::string OpenGLShader::GetFilepath() const
	{
		return this->m_filepath;
	}

	OpenGLShader::OpenGLShader(std::string const& filepath)
	{		
        VOLUND_INFO("Loading Shader (%s)... ", filepath.c_str());
		ShaderLoader loader = ShaderLoader(filepath);
		auto source = loader.GetSource();
		this->m_materialBlueprint = loader.GetBlueprint();
		this->m_filepath = filepath;

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &this->m_maxTextureUnit);
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

		this->m_id = program;
	}

	OpenGLShader::~OpenGLShader()
	{
		if (this->m_id != 0)
		{
			glDeleteProgram(this->m_id);
		}
	}
} //namespace Volund