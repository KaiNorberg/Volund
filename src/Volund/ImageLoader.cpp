#include "ImageLoader.h"

#include "Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Volund
{
	int32_t ImageLoader::GetWidth() const
	{
		return this->m_width;
	}

	int32_t ImageLoader::GetHeight() const
	{
		return this->m_height;
	}

	int32_t ImageLoader::GetChannels() const
	{
		return this->m_channels;
	}

	unsigned char* ImageLoader::GetData() const
	{
		return this->m_data;
	}

	void ImageLoader::Load(std::string const& filepath)
	{
		if (this->m_data != nullptr)
		{
			stbi_image_free(this->m_data);
		}

		stbi_set_flip_vertically_on_load(this->m_flip);
		this->m_data = stbi_load(filepath.c_str(), &this->m_width, &this->m_height, &this->m_channels, 4);

		if (this->m_data == nullptr)
		{
			VOLUND_WARNING("Unable to load image (%s)!", filepath.c_str());
		}
	}

	ImageLoader::ImageLoader(std::string const& filepath, bool flip)
	{
		this->m_flip = flip;
		this->Load(filepath);
	}

	ImageLoader::~ImageLoader()
	{
		stbi_image_free(this->m_data);
	}
}
