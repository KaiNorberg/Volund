#pragma once

#include "Texture.h"

namespace Volund
{
	class OpenGLTexture : public Texture
	{
	public:

		void Bind(uint32_t Unit) override;

		OpenGLTexture(const std::string& Filepath);

		~OpenGLTexture() override;

	private:
	};
}
