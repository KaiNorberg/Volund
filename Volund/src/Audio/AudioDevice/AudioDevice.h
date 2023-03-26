#pragma once

struct ALCdevice;

namespace Volund
{
	class AudioDevice
	{
	public:

		ALCdevice* GetDevice() const;

		AudioDevice(const char* device);
		
		~AudioDevice();

	private:
		
		ALCdevice* m_Device;
	};
}