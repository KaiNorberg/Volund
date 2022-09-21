#pragma once

#include "Vertexbuffer.h"

namespace Volund
{
	class OpenGLVertexbuffer : public Vertexbuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		void SetLayout(const VertexLayout& Layout) override;
		VertexLayout GetLayout() override;

		OpenGLVertexbuffer(float Vertices[], uint32_t Count);

		~OpenGLVertexbuffer() override;

	private:
		VertexLayout _Layout;

		uint32_t _ID;
	};
}
