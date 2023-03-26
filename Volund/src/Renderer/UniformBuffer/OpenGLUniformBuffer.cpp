#include "PCH/PCH.h"
#include "OpenGLUniformBuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLUniformBuffer::Set(const std::string& name, const void* data)
	{
		if (this->m_Id != 0)
		{
			Uniform uniform = this->m_Uniforms[name];
			glBindBuffer(GL_UNIFORM_BUFFER, this->m_Id);
			glBufferSubData(GL_UNIFORM_BUFFER, uniform.Offset, uniform.DataSize, data);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		else
		{
			VOLUND_INFO("Uniform Buffer Not Allocated!");
		}
	}

	void OpenGLUniformBuffer::Allocate()
	{
		glGenBuffers(1, &this->m_Id);
		glBindBuffer(GL_UNIFORM_BUFFER, this->m_Id);
		glBufferData(GL_UNIFORM_BUFFER, this->m_Size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::Assign(const uint32_t binding)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, this->m_Id);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, this->m_Id);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (this->m_Id != 0)
		{
			glDeleteBuffers(1, &this->m_Id);
		}
	}

}