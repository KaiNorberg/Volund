#include "PCH/PCH.h"

#include "OpenGLVertexbuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLVertexbuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	}

	void OpenGLVertexbuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexbuffer::SetLayout(const VertexLayout& layout)
	{
		this->m_Layout = layout;
	}

	VertexLayout OpenGLVertexbuffer::GetLayout()
	{
		return this->m_Layout;
	}

	OpenGLVertexbuffer::OpenGLVertexbuffer(const float vertices[], const uint32_t count)
	{
		glCreateBuffers(1, &this->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexbuffer::~OpenGLVertexbuffer()
	{
		glDeleteBuffers(1, &this->m_ID);
	}
}
