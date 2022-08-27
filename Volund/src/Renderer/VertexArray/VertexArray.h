#pragma once

#include "Renderer/VertexBuffer/VertexBuffer.h"
#include "Renderer/IndexBuffer/IndexBuffer.h"

namespace Volund
{
	class VertexArray
	{
	public:

		virtual void Bind() = 0;

		virtual void Unbind() = 0;

		virtual void SetVertexBuffer(VertexBuffer* Buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* Buffer) = 0;

		static VertexArray* Create();

		virtual ~VertexArray() = default;

	protected:
	};
}
