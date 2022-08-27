#pragma once

#include "VertexArray.h"

namespace Volund
{
	class OpenGLVertexArray : public VertexArray
	{
	public:

		void Bind() override;

		void Unbind() override;

		void SetVertexBuffer(VertexBuffer* Buffer) override;
		void SetIndexBuffer(IndexBuffer* Buffer) override;

		OpenGLVertexArray();
		
		~OpenGLVertexArray();

	private:

		uint32_t _ID;
	};
}
