#include "PCH/PCH.h"

#include "OpenGLIndexbuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLIndexbuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ID);
	}

	void OpenGLIndexbuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexbuffer::OpenGLIndexbuffer(uint32_t Indices[], uint32_t Count)
	{
		this->_Count = Count;
		glCreateBuffers(1, &this->_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->_ID);
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexbuffer::~OpenGLIndexbuffer()
	{
		glDeleteBuffers(1, &this->_ID);
	}
}
