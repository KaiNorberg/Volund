#include "PCH/PCH.h"

#include "OpenGLVertexbuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLVertexbuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_ID);
	}

	void OpenGLVertexbuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexbuffer::SetLayout(const VertexLayout& Layout)
	{
		this->_Layout = Layout;
	}

	VertexLayout OpenGLVertexbuffer::GetLayout()
	{
		return this->_Layout;
	}

	OpenGLVertexbuffer::OpenGLVertexbuffer(float Vertices[], uint32_t Count)
	{
		glCreateBuffers(1, &this->_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->_ID);
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(float), Vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexbuffer::~OpenGLVertexbuffer()
	{
		glDeleteBuffers(1, &this->_ID);
	}
}
