#pragma once

#include "VertexLayout/VertexLayout.h"

namespace Volund
{
	class VertexBuffer
	{
	public:
		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		uint32_t GetCount() const;

		virtual void SetLayout(const VertexLayout& Layout) = 0;
		virtual VertexLayout GetLayout() = 0;

		static Ref<VertexBuffer> Create(float Vertices[], uint32_t Count);

		virtual ~VertexBuffer() = default;
	private:
		uint32_t _Count;
	};
}
