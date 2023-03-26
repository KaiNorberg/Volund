#pragma once

#include "Mesh.h"

namespace Volund
{
	class OpenGLMesh : public Mesh
	{
	public:
		void Bind() const override;

		void Unbind() const override;

		void SetVertexbuffer(Ref<Vertexbuffer>& buffer) override;
		void SetIndexbuffer(Ref<Indexbuffer>& buffer) override;

		OpenGLMesh();

		OpenGLMesh(Ref<Vertexbuffer>& vertexBuffer, Ref<Indexbuffer>& indexBuffer);

		~OpenGLMesh() override;

	private:
		uint32_t m_ID;
	};
}
