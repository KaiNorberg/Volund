#pragma once

#include "UniformBuffer.h"

namespace Volund
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		void SetData(const void* data, uint32_t size, uint32_t offset) override;

		OpenGLUniformBuffer(uint32_t size, uint32_t binding);

		~OpenGLUniformBuffer();

	private:

	};
}

