#include "PCH/PCH.h"
#include "ImageLoader.h"

#include "stb/stb_image.h"

namespace Volund
{
	int32_t ImageLoader::GetWidth()
	{
		return this->_Width;
	}
	int32_t ImageLoader::GetHeight()
	{
		return this->_Height;
	}
	int32_t ImageLoader::GetChannels()
	{
		return this->_Channels;
	}

	unsigned char* ImageLoader::GetData()
	{
		return this->_Data;
	}

	ImageLoader::ImageLoader(std::string const& FilePath, int32_t DesiredChannels)
	{
		stbi_set_flip_vertically_on_load(true);
		this->_Data = stbi_load(FilePath.c_str(), &this->_Width, &this->_Height, &this->_Channels, DesiredChannels);

		VOLUND_ASSERT(this->_Data, "Failed to load image (%s)!", FilePath.c_str());
	}

	ImageLoader::~ImageLoader()
	{
		stbi_image_free(this->_Data);
	}
}