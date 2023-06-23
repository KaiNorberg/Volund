#include "PCH/PCH.h"
#include "ImageLoader.h"

#include "stb/stb_image.h"

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

	ImageLoader::ImageLoader(const std::string& filepath, bool flip, int32_t desiredChannels)
	{
		stbi_set_flip_vertically_on_load(flip);

		this->m_Data = stbi_load(filepath.c_str(), &this->m_Width, &this->m_Height, &this->m_Channels, desiredChannels);

		if (this->m_Data == nullptr)
		{
			VOLUND_WARNING("Unable to load image (%s)!", filepath.c_str());
		}
	}

	ImageLoader::~ImageLoader()
	{
		stbi_image_free(this->m_Data);
	}
}
