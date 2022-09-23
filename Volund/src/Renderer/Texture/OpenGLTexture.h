#pragma once

#include "Texture.h"

namespace Volund
{
	class OpenGLTexture : public Texture
	{
	public:

		void Bind(uint32_t Unit) override;

		OpenGLTexture(std::string_view Filepath);

		~OpenGLTexture() override;

	private:
		uint32_t _ID = 0;
	};
}
