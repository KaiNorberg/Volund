#include "PCH/PCH.h"

#include "OpenGLIndexBuffer.h"

namespace Volund
{
	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_Buffer);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t Indices[], uint32_t Count)
	{
		this->_Count = Count;
		glCreateBuffers(1, &this->_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->_Buffer);
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &this->_Buffer);
	}
}