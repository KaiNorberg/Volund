#include "PCH/PCH.h"
#include "Texture.h"

#include "OpenGLTexture.h"

#include <glad/glad.h>

#include "ImageLoader/ImageLoader.h"

namespace Volund
{
	uint32_t OpenGLTexture::GetID() const
	{
		return this->m_Id;
	}

	uint32_t OpenGLTexture::GetWidth() const
	{
		return this->m_Width;
	}

	uint32_t OpenGLTexture::GetHeight() const
	{
		return this->m_Height;
	}

	void OpenGLTexture::Bind(uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, this->m_Id);
	}

	void OpenGLTexture::SetData(unsigned char* data, uint32_t width, uint32_t height)
	{
		this->m_Width = width;
		this->m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &this->m_Id);
		glBindTexture(GL_TEXTURE_2D, this->m_Id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(this->m_Id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->m_Id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->m_Id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture::OpenGLTexture()
	{

	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &this->m_Id);
	}
}
