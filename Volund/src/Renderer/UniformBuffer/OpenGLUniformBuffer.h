#pragma once

#include "UniformBuffer.h"

namespace Volund
{
	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:

		void Set(const std::string& Name, const void* Data) override;

		void Allocate() override;

		void Assign(uint32_t Binding) override;

		~OpenGLUniformBuffer();

	private:

	};
}

