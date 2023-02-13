#pragma once

struct ALCdevice;

namespace Volund
{
	class AudioDevice
	{
	public:

		ALCdevice* GetDevice() const;

		AudioDevice(const char* Device);
		
		~AudioDevice();

	private:
		
		ALCdevice* _Device;
	};
}