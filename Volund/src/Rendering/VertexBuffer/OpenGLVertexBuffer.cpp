#include "PCH/PCH.h"

#include "OpenGLVertexBuffer.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	AABB OpenGLVertexBuffer::GetAABB()
	{
		return this->m_AABB;
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_Id);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLVertexBuffer::GetCount()
	{
		return this->m_Count;
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
		glCreateBuffers(1, &this->m_Id);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_Id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

		this->m_AABB = AABB(vertices, count);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &this->m_Id);
	}
}
