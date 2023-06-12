#include "PCH/PCH.h"

#include "OpenGLVertexBuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const VertexLayout& layout)
	{
		this->m_Layout = layout;
	}

	VertexLayout OpenGLVertexBuffer::GetLayout()
	{
		return this->m_Layout;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float vertices[], const uint32_t count)
	{
		glCreateBuffers(1, &this->m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_ID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

		this->m_AABB = AABB(vertices, count);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &this->m_ID);
	}
}
