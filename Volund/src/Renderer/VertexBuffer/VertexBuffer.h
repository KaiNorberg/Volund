#pragma once

#include "VertexLayout/VertexLayout.h"

#include "AABB/AABB.h"

namespace Volund
{
	class VertexBuffer
	{
	public:

		AABB GetAABB();

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual void SetLayout(const VertexLayout& layout) = 0;

		virtual VertexLayout GetLayout() = 0;

		static Ref<VertexBuffer> Create(const float vertices[], uint32_t count);

		virtual ~VertexBuffer() = default;

	protected:

		AABB m_AABB = {};
	};
}
