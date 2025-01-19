#include "Rendering/Texture.h"

#include "Rendering/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>

#include "ImageLoader.h"

namespace Volund
{
	std::string OpenGLTexture::GetFilepath() const
	{
		return this->m_filepath;
	}

    uint32_t OpenGLTexture::GetID() const
	{
		return this->m_id;
	}

	uint32_t OpenGLTexture::GetWidth() const
	{
		return this->m_width;
	}

	uint32_t OpenGLTexture::GetHeight() const
	{
		return this->m_height;
	}

	void OpenGLTexture::Bind(uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, this->m_id);
	}

	void OpenGLTexture::SetData(unsigned char* data, uint32_t width, uint32_t height)
	{
		this->m_width = width;
		this->m_height = height;

		if (this->m_id != 0)
		{
			glDeleteTextures(1, &this->m_id);
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &this->m_id);
		glBindTexture(GL_TEXTURE_2D, this->m_id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_width, this->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		glTextureParameteri(this->m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(this->m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(this->m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(this->m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

    OpenGLTexture::OpenGLTexture(std::string const& filepath)
    {
		this->m_filepath = filepath;
		ImageLoader loader = ImageLoader(filepath);
		this->SetData(loader.GetData(), loader.GetWidth(), loader.GetHeight());
    }

    OpenGLTexture::OpenGLTexture(unsigned char* data, uint32_t width, uint32_t height)
    {
		this->SetData(data, width, height);
    }

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &this->m_id);
	}
}