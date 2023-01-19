#include "PCH/PCH.h"
#include "AudioBuffer.h"

#include "Audio/Audio.h"
#include "AudioFile/AudioFile.h"

#include "Filesystem/Filesystem.h"

namespace Volund
{
	uint32_t AudioBuffer::GetBuffer() const
	{
		return this->_Buffer;
	}

	AudioBuffer::AudioBuffer(const std::string& Filepath)
	{
		AudioFile<float> File;
		std::vector<uint8_t> PCMDataBytes;

		if (!File.load(Filesystem::GetFinalPath(Filepath)))
		{
			VOLUND_WARNING("Failed to load sound (%s)!", Filepath.c_str());
		}
		File.writePCMToBuffer(PCMDataBytes);

		int AudioFormat = 0;		
		if (File.getBitDepth() == 16)
		{
			AudioFormat = File.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		}
		else if (File.getBitDepth() == 8)
		{
			AudioFormat = File.isStereo() ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		}
		else
		{
			VOLUND_WARNING("Invalid bit depth of %d in sound file (%s)!", File.getBitDepth(), Filepath.c_str());
		}

		alCall(alGenBuffers, 1, &this->_Buffer);
		alCall(alBufferData, this->_Buffer, AudioFormat, PCMDataBytes.data(), PCMDataBytes.size(), File.getSampleRate());
	}

	AudioBuffer::~AudioBuffer()
	{
		alCall(alDeleteBuffers, 1, &this->_Buffer);
	}
}