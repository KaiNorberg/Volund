#include "Rendering/Mesh.h"

#include "Rendering/OpenGL/OpenGLMesh.h"

#include "Rendering/RenderingAPI.h"

#include <glad/glad.h>

namespace Volund
{
	AABB OpenGLMesh::GetAABB(const Mat4x4& modelMatrix)
	{
		if (this->m_vertexBuffer == nullptr)
		{
			return AABB();
		}

		return this->m_vertexBuffer->GetAABB().ToWorldSpace(modelMatrix);
	}

	void OpenGLMesh::Bind() const
	{
		glBindVertexArray(this->m_id);
	}

	void OpenGLMesh::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLMesh::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
	{
		this->m_vertexBuffer = buffer;

		glBindVertexArray(this->m_id);
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

	void OpenGLMesh::SetIndexBuffer(std::shared_ptr<IndexBuffer> buffer)
	{
		this->m_indexBuffer = buffer;

		glBindVertexArray(this->m_id);
		buffer->Bind();
	}

	std::shared_ptr<VertexBuffer> OpenGLMesh::GetVertexBuffer()
	{
		return this->m_vertexBuffer;
	}

	std::shared_ptr<IndexBuffer> OpenGLMesh::GetIndexBuffer()
	{
		return this->m_indexBuffer;
	}

	const std::shared_ptr<VertexBuffer> OpenGLMesh::GetVertexBuffer() const
	{
		return this->m_vertexBuffer;
	}

	const std::shared_ptr<IndexBuffer> OpenGLMesh::GetIndexBuffer() const
	{
		return this->m_indexBuffer;
	}

	OpenGLMesh::OpenGLMesh()
	{
		glGenVertexArrays(1, &this->m_id);
	}

	OpenGLMesh::OpenGLMesh(std::shared_ptr<VertexBuffer> VertexBuffer, std::shared_ptr<IndexBuffer> IndexBuffer)
	{
		glGenVertexArrays(1, &this->m_id);
		this->SetVertexBuffer(VertexBuffer);
		this->SetIndexBuffer(IndexBuffer);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &this->m_id);
	}
}