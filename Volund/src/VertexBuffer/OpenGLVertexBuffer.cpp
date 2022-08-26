#include "PCH/PCH.h"

#include "OpenGLVertexBuffer.h"

namespace Volund
{
	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, this->_Buffer);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(VertexLayout const& Layout)
	{
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

	OpenGLVertexBuffer::OpenGLVertexBuffer(float Vertices[], uint32_t Count)
	{
		this->_Count = Count;
		glCreateBuffers(1, &this->_Buffer);
		this->Bind();
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(float), Vertices, GL_STATIC_DRAW);
	}
}