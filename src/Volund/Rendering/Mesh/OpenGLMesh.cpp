#include "PCH/PCH.h"
#include "Mesh.h"

#include "OpenGLMesh.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include <glad/glad.h>

namespace Volund
{
	AABB OpenGLMesh::GetAABB(const Mat4x4& modelMatrix)
	{
		if (this->m_VertexBuffer == nullptr)
		{
			return AABB();
		}

		return this->m_VertexBuffer->GetAABB().ToWorldSpace(modelMatrix);
	}

	void OpenGLMesh::Bind() const
	{
		glBindVertexArray(this->m_Id);
	}

	void OpenGLMesh::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLMesh::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
	{
		this->m_VertexBuffer = buffer;

		glBindVertexArray(this->m_Id);
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
		this->m_IndexBuffer = buffer;

		glBindVertexArray(this->m_Id);
		buffer->Bind();
	}

	std::shared_ptr<VertexBuffer> OpenGLMesh::GetVertexBuffer()
	{
		return this->m_VertexBuffer;
	}

	std::shared_ptr<IndexBuffer> OpenGLMesh::GetIndexBuffer()
	{
		return this->m_IndexBuffer;
	}

	const std::shared_ptr<VertexBuffer> OpenGLMesh::GetVertexBuffer() const
	{
		return this->m_VertexBuffer;
	}

	const std::shared_ptr<IndexBuffer> OpenGLMesh::GetIndexBuffer() const
	{
		return this->m_IndexBuffer;
	}

	OpenGLMesh::OpenGLMesh()
	{
		glGenVertexArrays(1, &this->m_Id);
	}

	OpenGLMesh::OpenGLMesh(std::shared_ptr<VertexBuffer> VertexBuffer, std::shared_ptr<IndexBuffer> IndexBuffer)
	{
		glGenVertexArrays(1, &this->m_Id);
		this->SetVertexBuffer(VertexBuffer);
		this->SetIndexBuffer(IndexBuffer);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &this->m_Id);
	}
}
