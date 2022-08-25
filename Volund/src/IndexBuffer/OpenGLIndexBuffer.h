#pragma once

#include "IndexBuffer.h"

namespace Volund
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:

		void Bind() override;

		void Unbind() override;

		OpenGLIndexBuffer(uint32_t Indices[], uint32_t Count);

	private:

		uint32_t _Buffer;
	};
}