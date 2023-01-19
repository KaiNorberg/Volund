#pragma once

namespace Volund
{
	class AudioBuffer
	{
	public:

		uint32_t GetBuffer() const;

		AudioBuffer(const std::string& Filepath);

		~AudioBuffer();

	private:

		uint32_t _Buffer;
	};
}
