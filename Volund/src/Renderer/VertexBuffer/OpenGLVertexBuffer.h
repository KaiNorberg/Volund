#pragma once

#include "Vertexbuffer.h"

namespace Volund
{
	class OpenGLVertexbuffer : public Vertexbuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		void SetLayout(const VertexLayout& layout) override;

		VertexLayout GetLayout() override;

		OpenGLVertexbuffer(const float vertices[], uint32_t count);

		~OpenGLVertexbuffer() override;

	private:
		VertexLayout m_Layout;

		uint32_t m_ID;
	};
}
