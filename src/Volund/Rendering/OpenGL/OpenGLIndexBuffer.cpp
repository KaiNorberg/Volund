
#include "Rendering/OpenGL/OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Volund
{
	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const
	{
		return this->m_count;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t indices[], uint64_t count)
	{
		this->m_count = count;
		glCreateBuffers(1, &this->m_id);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &this->m_id);
	}
}