#pragma once

namespace Volund
{
	class AudioBuffer
	{
	public:

		uint32_t GetBuffer() const;

		AudioBuffer(const std::string& filepath);

		~AudioBuffer();

	private:

		uint32_t m_Buffer = 0;
	};
}
