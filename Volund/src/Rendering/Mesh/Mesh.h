#pragma once

#include "Rendering/IndexBuffer/IndexBuffer.h"
#include "Rendering/VertexBuffer/VertexBuffer.h"

#include "AABB/AABB.h"

#include "ResourceLibrary/ResourceLibrary.h"

namespace Volund
{
	class Mesh
	{
	public:

		AABB GetAABB(const Mat4x4& modelMatrix);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(Ref<VertexBuffer> buffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer> buffer) = 0;

		Ref<VertexBuffer> GetVertexBuffer();
		Ref<IndexBuffer> GetIndexBuffer();

		const Ref<VertexBuffer> GetVertexBuffer() const;
		const Ref<IndexBuffer> GetIndexBuffer() const;

		static Ref<Mesh> Create();

		static Ref<Mesh> Create(const std::string& filepath);

		static Ref<Mesh> Create(Ref<VertexBuffer> vertexBuffer, Ref<IndexBuffer> indexBuffer);

		static Ref<Mesh> CreateAsync(const std::string& filepath);

		virtual ~Mesh() = default;

	protected:

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	
	private:
	};
}
