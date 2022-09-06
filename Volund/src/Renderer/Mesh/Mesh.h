#pragma once

#include "Renderer/VertexBuffer/VertexBuffer.h"
#include "Renderer/IndexBuffer/IndexBuffer.h"

namespace Volund
{
	class Mesh
	{
	public:

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(Ref<VertexBuffer>& Buffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& Buffer) = 0;

		Ref<VertexBuffer> GetVertexBuffer();
		Ref<IndexBuffer> GetIndexBuffer();
		const Ref<VertexBuffer> GetVertexBuffer() const;
		const Ref<IndexBuffer> GetIndexBuffer() const;

		static Ref<Mesh> Create(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer);

		virtual ~Mesh() = default;

	protected:

		Ref<VertexBuffer> _VertexBuffer;
		Ref<IndexBuffer> _IndexBuffer;
	};
}
