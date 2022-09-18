#pragma once

#include "Renderer/IndexBuffer/IndexBuffer.h"
#include "Renderer/VertexBuffer/VertexBuffer.h"

namespace Volund
{
	class Mesh
	{
	public:

		std::string GetFilePath();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetVertexBuffer(Ref<VertexBuffer>& Buffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& Buffer) = 0;

		Ref<VertexBuffer> GetVertexBuffer();
		Ref<IndexBuffer> GetIndexBuffer();
		const Ref<VertexBuffer> GetVertexBuffer() const;
		const Ref<IndexBuffer> GetIndexBuffer() const;

		static Ref<Mesh> Create(std::string_view FilePath);

		static Ref<Mesh> Create(Ref<VertexBuffer>& VBuffer, Ref<IndexBuffer>& IBuffer);

		virtual ~Mesh() = default;

	protected:

		std::string _FilePath;

		Ref<VertexBuffer> _VertexBuffer;
		Ref<IndexBuffer> _IndexBuffer;
	};
}
