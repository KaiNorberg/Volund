#pragma once

#include "Mesh.h"

namespace Volund
{
	class OpenGLMesh : public Mesh
	{
	public:

		AABB GetAABB(const Mat4x4& modelMatrix) override;

		void Bind() const override;

		void Unbind() const override;

		void SetVertexBuffer(Ref<VertexBuffer> buffer) override;
		void SetIndexBuffer(Ref<IndexBuffer> buffer) override;

		Ref<VertexBuffer> GetVertexBuffer() override;
		Ref<IndexBuffer> GetIndexBuffer() override;

		const Ref<VertexBuffer> GetVertexBuffer() const override;
		const Ref<IndexBuffer> GetIndexBuffer() const override;

		OpenGLMesh();

		OpenGLMesh(Ref<VertexBuffer> VertexBuffer, Ref<IndexBuffer> IndexBuffer);

		~OpenGLMesh() override;

	private:

		uint32_t m_Id;

		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
