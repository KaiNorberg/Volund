#pragma once

#include "Texture.h"

namespace Volund
{
	class OpenGLTexture : public Texture
	{
	public:

		void Bind(uint32_t unit) override;

		OpenGLTexture(const std::string& filepath);

		~OpenGLTexture() override;

	private:
	};
}
