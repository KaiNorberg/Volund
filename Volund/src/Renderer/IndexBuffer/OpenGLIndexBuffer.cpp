#include "PCH/PCH.h"

#include "OpenGLIndexbuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLIndexbuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ID);
	}

	void OpenGLIndexbuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexbuffer::OpenGLIndexbuffer(const uint32_t indices[], uint32_t count)
	{
		this->m_Count = count;
		glCreateBuffers(1, &this->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexbuffer::~OpenGLIndexbuffer()
	{
		glDeleteBuffers(1, &this->m_ID);
	}
}
