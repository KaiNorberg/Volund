#pragma once

#include "VertexLayout/VertexLayout.h"

namespace Volund
{
	class Vertexbuffer
	{
	public:
		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		uint32_t GetCount() const;

		virtual void SetLayout(const VertexLayout& layout) = 0;

		virtual VertexLayout GetLayout() = 0;

		static Ref<Vertexbuffer> Create(const float vertices[], uint32_t count);

		virtual ~Vertexbuffer() = default;
	private:
		uint32_t m_Count = 0;
	};
}
