#include "PCH/PCH.h"
#include "Mesh.h"

#include "OpenGLMesh.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

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

	void OpenGLMesh::SetVertexbuffer(Ref<Vertexbuffer>& buffer)
	{
		this->m_Vertexbuffer = buffer;

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

	void OpenGLMesh::SetIndexbuffer(Ref<Indexbuffer>& buffer)
	{
		this->m_Indexbuffer = buffer;

		glBindVertexArray(this->m_ID);
		buffer->Bind();
	}

	OpenGLMesh::OpenGLMesh()
	{
		glGenVertexArrays(1, &this->m_ID);
	}

	OpenGLMesh::OpenGLMesh(Ref<Vertexbuffer>& vertexBuffer, Ref<Indexbuffer>& indexBuffer)
	{
		glGenVertexArrays(1, &this->m_ID);
		this->SetVertexbuffer(vertexBuffer);
		this->SetIndexbuffer(indexBuffer);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &this->m_ID);
	}
}
