#include "PCH/PCH.h"

#include "OpenGLVertexBuffer.h"

#include <glad/include/glad/glad.h>

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

	void OpenGLVertexBuffer::SetLayout(VertexLayout const& Layout)
	{
		this->_Layout = Layout;
	}

	VertexLayout OpenGLVertexBuffer::GetLayout()
	{
		return this->_Layout;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float Vertices[], uint32_t Count)
	{
		glCreateBuffers(1, &this->_Buffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->_Buffer);
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(float), Vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &this->_Buffer);
	}
}