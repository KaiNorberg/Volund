#pragma once

#include "Texture.h"

namespace Volund
{
	class OpenGLTexture : public Texture
	{
	public:
		std::string GetFilePath();

		void Bind(uint32_t Unit) override;

		OpenGLTexture(const std::string& FilePath);

		~OpenGLTexture() override;

	private:
		uint32_t _ID = 0;
	};
}
