#include "PCH/PCH.h"

#include "OpenGLVertexBuffer.h"

namespace Volund
{
	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_Buffer);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float Vertices[], uint32_t Count)
	{
		this->_Count = Count;
		glCreateBuffers(1, &this->_Buffer);
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(float), Vertices, GL_STATIC_DRAW);
	}
}