#pragma once

#include "VertexBuffer.h"

namespace Volund
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		
		AABB GetAABB() override;

		void Bind() override;

		void Unbind() override;

		uint32_t GetCount() override;

		void SetLayout(const VertexLayout& layout) override;

		VertexLayout GetLayout() override;

		OpenGLVertexBuffer(const float vertices[], uint32_t count);

		~OpenGLVertexBuffer() override;

	private:

		AABB m_AABB = {};

		VertexLayout m_Layout;
		
		uint32_t m_Count;

		uint32_t m_Id;
	};
}
