#pragma once

#include "Indexbuffer.h"

namespace Volund
{
	class OpenGLIndexbuffer : public Indexbuffer
	{
	public:
		void Bind() override;

		void Unbind() override;

		OpenGLIndexbuffer(const uint32_t Indices[], uint32_t Count);

		~OpenGLIndexbuffer() override;

	private:
		uint32_t _ID;
	};
}
