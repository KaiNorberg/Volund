#pragma once

#include "UniformBuffer.h"

namespace Volund
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		void Set(const std::string& name, const void* data) override;

		void Allocate() override;

		void Assign(uint32_t binding) override;

		~OpenGLUniformBuffer();

	private:

	};
}

