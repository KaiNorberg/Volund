#include "PCH/PCH.h"
#include "Mesh.h"

#include "OpenGLMesh.h"

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

	void OpenGLMesh::SetVertexBuffer(Ref<VertexBuffer>& Buffer)
	{
		this->_VertexBuffer = Buffer;

		glBindVertexArray(this->_ID);
		Buffer->Bind();

		VertexLayout Layout = Buffer->GetLayout();
		uint32_t Stride = 0;
		for (int i = 0; i < Layout.size(); i++)
		{
			Stride += Layout[i].GetByteSize();
		}

		uint64_t Offset = 0;
		for (int i = 0; i < Layout.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, Layout[i].GetElementCount(), Layout[i].GetDataType(), GL_FALSE, Stride,
			                      (const void*)Offset);
			Offset += Layout[i].GetByteSize();
		}
	}

	void OpenGLMesh::SetIndexBuffer(Ref<IndexBuffer>& Buffer)
	{
		this->_IndexBuffer = Buffer;

		glBindVertexArray(this->_ID);
		Buffer->Bind();
	}

	OpenGLMesh::OpenGLMesh(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer)
	{
		glGenVertexArrays(1, &this->_ID);
		this->SetVertexBuffer(VBuffer);
		this->SetIndexBuffer(IBuffer);
	}

	OpenGLMesh::~OpenGLMesh()
	{
		glDeleteVertexArrays(1, &this->_ID);
	}
}
