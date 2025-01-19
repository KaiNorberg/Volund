#include "Audio/AudioBuffer.h"

#include "Audio/Audio.h"
#include "Logger.h"

#include <AudioFile/AudioFile.h>
#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
	uint32_t AudioBuffer::GetBuffer() const
	{
		return this->m_buffer;
	}

	AudioBuffer::AudioBuffer(std::string const& filepath)
	{
		AudioFile<float> file;
		std::vector<uint8_t> pcmDataBytes;

		if (!file.load(filepath))
		{
			VOLUND_WARNING("Unable to load sound file (%s)!", filepath.c_str());
			return;
		}
		file.writePCMToBuffer(pcmDataBytes);

		int audioFormat = 0;
		if (file.getBitDepth() == 32)
		{
			audioFormat = file.isStereo() ? AL_FORMAT_STEREO_FLOAT32 : AL_FORMAT_MONO_FLOAT32;
		}
		else if (file.getBitDepth() == 16)
		{
			audioFormat = file.isStereo() ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
		}
		else if (file.getBitDepth() == 8)
		{
			audioFormat = file.isStereo() ? AL_FORMAT_STEREO8 : AL_FORMAT_MONO8;
		}
		else
		{
			VOLUND_WARNING("Invalid bit depth of %d in sound file (%s)!", file.getBitDepth(), filepath.c_str());
		}

		AL_CALL(alGenBuffers, 1, &this->m_buffer);
		AL_CALL(alBufferData, this->m_buffer, audioFormat, pcmDataBytes.data(), pcmDataBytes.size(), file.getSampleRate());
	}

	AudioBuffer::~AudioBuffer()
	{
		if (this->m_buffer != 0 && alIsBuffer(this->m_buffer))
		{
			AL_CALL(alDeleteBuffers, 1, &this->m_buffer);
			this->m_buffer = 0;
		}
	}
}