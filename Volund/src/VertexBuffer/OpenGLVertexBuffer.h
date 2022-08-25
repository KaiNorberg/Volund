#pragma once

#include "VertexBuffer.h"

namespace Volund
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		void Bind() override;

		void Unbind() override;

		OpenGLVertexBuffer(float Vertices[], uint32_t Count);

	private:

		uint32_t _Buffer;
	};
}