#include "PCH/PCH.h"
#include "Texture.h"

#include "OpenGLTexture.h"

#include <glad/include/glad/glad.h>

#include "ImageLoader/ImageLoader.h"

#include "DelayedTaskHandler/DelayedTaskHandler.h"
#include "ThreadPool/ThreadPool.h"

namespace Volund
{
	void OpenGLTexture::Bind(uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, this->m_ID);
	}

	OpenGLTexture::OpenGLTexture(const std::string& filepath)
	{
		VOLUND_THREADPOOL_SUBMIT([this, filepath]()
		{
			Ref<ImageLoader> loader = std::make_shared<ImageLoader>(filepath, 4);

			DelayedTaskHandler::DelayTask([this, filepath, loader]()
			{
				this->m_Width = loader->GetWidth();
				this->m_Height = loader->GetHeight();
				this->m_Filepath = filepath;

				glCreateTextures(GL_TEXTURE_2D, 1, &this->m_ID);
				glBindTexture(GL_TEXTURE_2D, this->m_ID);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
					loader->GetData());

				glTextureParameteri(this->m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTextureParameteri(this->m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				glTextureParameteri(this->m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTextureParameteri(this->m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
			});
		});
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &this->m_ID);
	}
}
