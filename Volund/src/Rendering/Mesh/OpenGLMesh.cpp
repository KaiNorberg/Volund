#include "PCH/PCH.h"
#include "Mesh.h"

#include "OpenGLMesh.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLMesh::Bind() const
	{
		glBindVertexArray(this->m_ID);
	}

	void OpenGLMesh::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLMesh::SetVertexBuffer(Ref<VertexBuffer>& buffer)
	{
		this->m_VertexBuffer = buffer;

		glBindVertexArray(this->m_ID);
		buffer->Bind();

		const VertexLayout layout = buffer->GetLayout();
		uint32_t stride = 0;
		for (uint64_t i = 0; i < layout.size(); i++)
		{
			stride += layout[i].GetByteSize();
		}

		uint64_t offset = 0;
		for (uint64_t i = 0; i < layout.size(); i++)
		{
			glEnableVertexAttribArray((GLuint)i);
			glVertexAttribPointer((GLuint)i, layout[i].GetElementCount(), layout[i].GetDataType(), GL_FALSE, stride, (const void*)offset);
			offset += layout[i].GetByteSize();
		}
	}

	void OpenGLMesh::SetIndexBuffer(Ref<IndexBuffer>& buffer)
	{
		this->m_IndexBuffer = buffer;

		glBindVertexArray(this->m_ID);
		buffer->Bind();
	}

	OpenGLMesh::OpenGLMesh()
	{
		glGenVertexArrays(1, &this->m_ID);
	}

	OpenGLMesh::OpenGLMesh(Ref<VertexBuffer>& VertexBuffer, Ref<IndexBuffer>& IndexBuffer)
	{
		glGenVertexArrays(1, &this->m_ID);
		this->SetVertexBuffer(VertexBuffer);
		this->SetIndexBuffer(IndexBuffer);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &this->m_ID);
	}
}
