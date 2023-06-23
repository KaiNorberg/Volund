#pragma once

#include "Mesh.h"

namespace Volund
{
	class OpenGLMesh : public Mesh
	{
	public:
		void Bind() const override;

		void Unbind() const override;

		void SetVertexBuffer(Ref<VertexBuffer> buffer) override;
		void SetIndexBuffer(Ref<IndexBuffer> buffer) override;

		OpenGLMesh();

		OpenGLMesh(Ref<VertexBuffer> VertexBuffer, Ref<IndexBuffer> IndexBuffer);

		~OpenGLMesh() override;

	private:
		uint32_t m_ID;
	};
}
