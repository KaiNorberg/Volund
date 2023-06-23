#pragma once

#include "VertexLayout/VertexLayout.h"

#include "AABB/AABB.h"

namespace Volund
{
	class VertexBuffer
	{
	public:

		virtual AABB GetAABB() = 0;

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual uint32_t GetCount() = 0;

		virtual void SetLayout(const VertexLayout& layout) = 0;

		virtual VertexLayout GetLayout() = 0;

		static Ref<VertexBuffer> Create(const float vertices[], uint32_t count);

		virtual ~VertexBuffer() = default;
	};
}
