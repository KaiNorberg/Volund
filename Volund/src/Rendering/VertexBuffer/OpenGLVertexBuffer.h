#pragma once

#include "VertexBuffer.h"

namespace Volund
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		void SetLayout(const VertexLayout& layout) override;

		VertexLayout GetLayout() override;

		OpenGLVertexBuffer(const float vertices[], uint32_t count);

		~OpenGLVertexBuffer() override;

	private:
		VertexLayout m_Layout;

		uint32_t m_ID;
	};
}
