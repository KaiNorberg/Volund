#include "PCH/PCH.h"
#include "VertexArray.h"

#include "Renderer/Renderer.h"

#include "OpenGLVertexArray.h"

namespace Volund
{
	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(this->_ID);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetVertexBuffer(VertexBuffer* Buffer)
	{
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
			glVertexAttribPointer(i, Layout[i].GetElementCount(), Layout[i].GetDataType(), GL_FALSE, Stride, (const void*)Offset);
			Offset += Layout[i].GetByteSize();
		}
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* Buffer)
	{
		glBindVertexArray(this->_ID);
		Buffer->Bind();
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &this->_ID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &this->_ID);
	}
}