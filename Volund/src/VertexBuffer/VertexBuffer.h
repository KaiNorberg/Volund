#pragma once

#include "VertexLayout/VertexLayout.h"

namespace Volund
{
	class VertexBuffer
	{
	public:

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual void SetLayout(VertexLayout const& Layout) = 0;

		uint32_t GetCount();

		static VertexBuffer* Create(float Vertices[], uint32_t Count);

	protected:
		uint32_t _Count;
	};
}