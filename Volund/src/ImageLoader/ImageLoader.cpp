#include "PCH/PCH.h"
#include "ImageLoader.h"

#include "stb/stb_image.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	int32_t ImageLoader::GetWidth() const
	{
		return this->_Width;
	}

	int32_t ImageLoader::GetHeight() const
	{
		return this->_Height;
	}

	int32_t ImageLoader::GetChannels() const
	{
		return this->_Channels;
	}

	unsigned char* ImageLoader::GetData() const
	{
		return this->_Data;
	}

	ImageLoader::ImageLoader(const std::string& Filepath, int32_t DesiredChannels)
	{
		std::string FinalPath = VL::Filesystem::GetFinalPath(Filepath);

		stbi_set_flip_vertically_on_load(true);
		this->_Data = stbi_load(FinalPath.c_str(), &this->_Width, &this->_Height, &this->_Channels, DesiredChannels);

		VOLUND_ASSERT(this->_Data, "Failed to load image (%s)!", FinalPath.c_str());
	}

	ImageLoader::~ImageLoader()
	{
		stbi_image_free(this->_Data);
	}
}
