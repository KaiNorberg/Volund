#include "ImageLoader.h"

#include "Logger.h"

#include <stb/stb_image.h>

namespace Volund
{
	int32_t ImageLoader::GetWidth() const
	{
		return this->m_Width;
	}

	int32_t ImageLoader::GetHeight() const
	{
		return this->m_Height;
	}

	int32_t ImageLoader::GetChannels() const
	{
		return this->m_Channels;
	}

	unsigned char* ImageLoader::GetData() const
	{
		return this->m_Data;
	}

	void ImageLoader::Load(std::string const& filepath)
	{
		if (this->m_Data != nullptr)
		{
			stbi_image_free(this->m_Data);
		}

		stbi_set_flip_vertically_on_load(true);
		this->m_Data = stbi_load(filepath.c_str(), &this->m_Width, &this->m_Height, &this->m_Channels, 4);

		if (this->m_Data == nullptr)
		{
			VOLUND_WARNING("Unable to load image (%s)!", filepath.c_str());
		}
	}

	ImageLoader::ImageLoader(std::string const& filepath)
	{
		this->Load(filepath);
	}

	ImageLoader::~ImageLoader()
	{
		stbi_image_free(this->m_Data);
	}
}
