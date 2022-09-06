#pragma once

namespace Volund
{
	class ImageLoader
	{
	public:

		int32_t GetWidth();

		int32_t GetHeight();

		int32_t GetChannels();

		unsigned char* GetData();

		ImageLoader(std::string const& FilePath, int32_t DesiredChannels);

		~ImageLoader();

	private:

		int32_t _Width;
		
		int32_t _Height;
		
		int32_t _Channels;

		unsigned char* _Data;
	};

}

