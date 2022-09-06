#pragma once

#include "Mesh.h"

namespace Volund
{
	class OpenGLMesh : public Mesh
	{
	public:

		void Bind() const override;

		void Unbind() const override;

		void SetVertexBuffer(Ref<VertexBuffer>& Buffer) override;
		void SetIndexBuffer(Ref<IndexBuffer>& Buffer) override;

		OpenGLMesh(std::string const& FilePath);

		OpenGLMesh(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer);
		
		~OpenGLMesh();

	private:
		uint32_t _ID;
	};
}
