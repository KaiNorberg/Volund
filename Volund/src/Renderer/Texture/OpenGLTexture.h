#pragma once

#include "Texture.h"

namespace Volund
{
	class OpenGLTexture2D : public Texture2D
	{
	public:

		void Bind(uint32_t Unit) override;

		OpenGLTexture2D(std::string const& FilePath);

		~OpenGLTexture2D();

	private:
		uint32_t _ID = 0;
	};
}
