#pragma once

#include "IndexBuffer.h"

namespace Volund
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		uint32_t GetCount() const override;

		OpenGLIndexBuffer(const uint32_t indices[], uint32_t count);

		~OpenGLIndexBuffer() override;

	private:

		uint32_t m_Count;

		uint32_t m_Id;
	};
}
