#include "PCH/PCH.h"
#include "Texture.h"

#include "Renderer/Renderer.h"

#include "OpenGLTexture.h"

#include <glad/include/glad/glad.h>

#include "stb/stb_image.h"

namespace Volund
{
	void OpenGLTexture2D::Bind(uint32_t Unit)
	{
		glActiveTexture(GL_TEXTURE0 + Unit);
		glBindTexture(GL_TEXTURE_2D, this->_ID);
	}

	OpenGLTexture2D::OpenGLTexture2D(std::string const& FilePath)
	{
		int Width, Height, ChannelCount = 0;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* Data = stbi_load(FilePath.c_str(), &Width, &Height, &ChannelCount, 4);
		this->_Width = Width;
		this->_Height = Height;

		VOLUND_ASSERT(Data, "Failed to load Texture2D (%s)!", FilePath.c_str());
	
		glCreateTextures(GL_TEXTURE_2D, 1, &this->_ID);
		glBindTexture(GL_TEXTURE_2D, this->_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->_Width, this->_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);

		glTextureParameteri(this->_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		stbi_image_free(Data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &this->_ID);
	}
}