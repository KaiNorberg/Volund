#pragma once

#include "Mesh.h"

namespace Volund
{
	class OpenGLMesh : public Mesh
	{
	public:
		void Bind() const override;

		void Unbind() const override;

		void SetVertexbuffer(Ref<Vertexbuffer>& Buffer) override;
		void SetIndexbuffer(Ref<Indexbuffer>& Buffer) override;

		OpenGLMesh(std::string_view Filepath);

		OpenGLMesh(Ref<Vertexbuffer>& VBuffer, Ref<Indexbuffer>& IBuffer);

		~OpenGLMesh() override;

	private:
		uint32_t _ID;
	};
}
