#include "Audio/AudioBuffer.hpp"

#include "Audio/Audio.hpp"
#include "Logger.hpp"
#include "Lua/LuaAPI.hpp"

#include <AudioFile/AudioFile.h>
#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
	std::string AudioBuffer::GetFilepath()
	{
		return this->m_filepath;
	}

	uint32_t AudioBuffer::GetBuffer() const
	{
		return this->m_buffer;
	}

	AudioBuffer::AudioBuffer(std::string const& filepath)
	{
		this->m_filepath = filepath;
		AudioFile<float> file;
		std::vector<uint8_t> pcmDataBytes;

		if (!file.load(filepath))
		{
			VOLUND_WARNING("Unable to load sound file ({})!", filepath.c_str());
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
			VOLUND_WARNING("Invalid bit depth of {} in sound file ({})!", file.getBitDepth(), filepath.c_str());
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

	VOLUND_USERTYPE_REGISTER(AudioBuffer,
    [](LuaState* state){
        state->NewUsertype<AudioBuffer>("AudioBuffer", sol::constructors<>(),
            "new", [state](std::string const& filepath) { return std::make_shared<AudioBuffer>(state->AbsolutePath(filepath)); }
        );
    });
}