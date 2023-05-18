#pragma once

#include "Renderer/IndexBuffer/IndexBuffer.h"
#include "Renderer/VertexBuffer/VertexBuffer.h"

#include "AABB/AABB.h"

namespace Volund
{
	class Mesh
	{
	public:

		AABB GetAABB(const Mat4x4& modelMatrix);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(Ref<VertexBuffer>& buffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& buffer) = 0;

		Ref<VertexBuffer> GetVertexBuffer();
		Ref<IndexBuffer> GetIndexBuffer();
		const Ref<VertexBuffer> GetVertexBuffer() const;
		const Ref<IndexBuffer> GetIndexBuffer() const;

		static Ref<Mesh> Create();

		static Ref<Mesh> Create(Ref<VertexBuffer>& VertexBuffer, Ref<IndexBuffer>& IndexBuffer);

		virtual ~Mesh() = default;

	protected:

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
