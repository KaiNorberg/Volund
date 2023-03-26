#pragma once

#include "Indexbuffer.h"

namespace Volund
{
	class OpenGLIndexbuffer : public Indexbuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		OpenGLIndexbuffer(const uint32_t indices[], uint32_t count);

		~OpenGLIndexbuffer() override;

	private:
		uint32_t m_ID;
	};
}
