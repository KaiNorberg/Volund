#pragma once

#include "VertexBuffer.h"

namespace Volund
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		void SetLayout(const VertexLayout& Layout) override;
		VertexLayout GetLayout() override;

		OpenGLVertexBuffer(float Vertices[], uint32_t Count);

		~OpenGLVertexBuffer() override;

	private:
		VertexLayout _Layout;

		uint32_t _Buffer;
	};
}
