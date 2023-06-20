#include "PCH/PCH.h"
#include "OpenGLUniformBuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLUniformBuffer::SetData(const void* data, uint32_t size, uint32_t offset)
	{
		glNamedBufferSubData(this->m_Id, offset, size, data);
	}

	OpenGLUniformBuffer::OpenGLUniformBuffer(uint32_t size, uint32_t binding)
	{
		glCreateBuffers(1, &this->m_Id);
		glNamedBufferData(this->m_Id, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, binding, this->m_Id);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		if (this->m_Id != 0)
		{
			glDeleteBuffers(1, &this->m_Id);
		}
	}

}