#include "PCH/PCH.h"

#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Volund
{
	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_Id);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return this->m_Count;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t indices[], uint64_t count)
	{
		this->m_Count = count;
		glCreateBuffers(1, &this->m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_Id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &this->m_Id);
	}
}
