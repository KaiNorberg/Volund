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

		OpenGLMesh(const std::string& FilePath);

		OpenGLMesh(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer);

		~OpenGLMesh() override;

	private:
		uint32_t _ID;
	};
}
