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

		ImageLoader(const std::string& filepath, int32_t desiredChannels = 4);

		~ImageLoader();

	private:
		int32_t m_Width;

		int32_t m_Height;

		int32_t m_Channels;

		unsigned char* m_Data;
	};
}
