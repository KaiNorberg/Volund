#include "PCH/PCH.h"
#include "Mesh.h"

#include "OpenGLMesh.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	void OpenGLMesh::Bind() const
	{
		glBindVertexArray(this->_ID);
	}

	void OpenGLMesh::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLMesh::SetVertexbuffer(Ref<Vertexbuffer>& Buffer)
	{
		this->_Vertexbuffer = Buffer;

		glBindVertexArray(this->_ID);
		Buffer->Bind();

		VertexLayout Layout = Buffer->GetLayout();
		uint32_t Stride = 0;
		for (uint64_t i = 0; i < Layout.size(); i++)
		{
			Stride += Layout[i].GetByteSize();
		}

		uint64_t Offset = 0;
		for (uint64_t i = 0; i < Layout.size(); i++)
		{
			glEnableVertexAttribArray((GLuint)i);
			glVertexAttribPointer((GLuint)i, Layout[i].GetElementCount(), Layout[i].GetDataType(), GL_FALSE, Stride, (const void*)Offset);
			Offset += Layout[i].GetByteSize();
		}
	}

	void OpenGLMesh::SetIndexbuffer(Ref<Indexbuffer>& Buffer)
	{
		this->_Indexbuffer = Buffer;

		glBindVertexArray(this->_ID);
		Buffer->Bind();
	}

	OpenGLMesh::OpenGLMesh(Ref<Vertexbuffer>& VBuffer, Ref<Indexbuffer>& IBuffer)
	{
		glGenVertexArrays(1, &this->_ID);
		this->SetVertexbuffer(VBuffer);
		this->SetIndexbuffer(IBuffer);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &this->_ID);
	}
}
