#pragma once

#include "Texture.h"

namespace Volund
{
	class OpenGLTexture : public Texture
	{
	public:

		void Bind(uint32_t unit) override;

		void SetData(unsigned char* data, uint32_t width, uint32_t height) override;

		OpenGLTexture();

		~OpenGLTexture() override;

	private:
	};
}
