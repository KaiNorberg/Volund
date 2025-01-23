
#include "Rendering/OpenGL/OpenGLVertexBuffer.hpp"

#include <glad/glad.h>

namespace Volund
{
	AABB OpenGLVertexBuffer::GetAABB()
	{
		return this->m_aABB;
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLVertexBuffer::GetCount()
	{
		return this->m_count;
	}

	void OpenGLVertexBuffer::SetLayout(const VertexLayout& layout)
	{
		this->m_layout = layout;
	}

	VertexLayout OpenGLVertexBuffer::GetLayout()
	{
		return this->m_layout;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float vertices[], const uint64_t count)
	{
		glCreateBuffers(1, &this->m_id);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_id);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), vertices, GL_STATIC_DRAW);

		this->m_aABB = AABB(vertices, count);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &this->m_id);
	}
}