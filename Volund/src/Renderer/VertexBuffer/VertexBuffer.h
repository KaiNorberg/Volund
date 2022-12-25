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

		virtual void SetLayout(const VertexLayout& Layout) = 0;

		virtual VertexLayout GetLayout() = 0;

		static Ref<Vertexbuffer> Create(const float Vertices[], uint32_t Count);

		virtual ~Vertexbuffer() = default;
	private:
		uint32_t _Count;
	};
}
