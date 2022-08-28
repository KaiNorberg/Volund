#pragma once

#include "VertexArray.h"

namespace Volund
{
	class OpenGLVertexArray : public VertexArray
	{
	public:

		void Bind() const override;

		void Unbind() const override;

		void SetVertexBuffer(Ref<VertexBuffer>& Buffer) override;
		void SetIndexBuffer(Ref<IndexBuffer>& Buffer) override;

		OpenGLVertexArray();

		OpenGLVertexArray(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer);
		
		~OpenGLVertexArray();

	private:
		uint32_t _ID;
	};
}
