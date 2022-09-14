#pragma once

namespace Volund
{
	class ImageLoader
	{
	public:
		int32_t GetWidth() const;

		int32_t GetHeight() const;

		int32_t GetChannels() const;

		unsigned char* GetData() const;

		ImageLoader(std::string_view FilePath, int32_t DesiredChannels);

		~ImageLoader();

	private:
		int32_t _Width;

		int32_t _Height;

		int32_t _Channels;

		unsigned char* _Data;
	};
}
