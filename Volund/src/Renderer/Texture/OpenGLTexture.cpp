#include "PCH/PCH.h"
#include "Texture.h"

#include "OpenGLTexture.h"

#include <glad/include/glad/glad.h>

#include "ImageLoader/ImageLoader.h"

namespace Volund
{
	void OpenGLTexture::Bind(uint32_t Unit)
	{
		glActiveTexture(GL_TEXTURE0 + Unit);
		glBindTexture(GL_TEXTURE_2D, this->_ID);
	}

	OpenGLTexture::OpenGLTexture(const std::string& FilePath)
	{
		ImageLoader Loader = ImageLoader(FilePath, 4);

		this->_Width = Loader.GetWidth();
		this->_Height = Loader.GetHeight();
		this->_FilePath = FilePath;

		glCreateTextures(GL_TEXTURE_2D, 1, &this->_ID);
		glBindTexture(GL_TEXTURE_2D, this->_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->_Width, this->_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		             Loader.GetData());

		glTextureParameteri(this->_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &this->_ID);
	}
}
