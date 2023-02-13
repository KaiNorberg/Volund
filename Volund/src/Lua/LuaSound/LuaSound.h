#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
	class LuaSound
	{
	public:

		Ref<AudioBuffer> GetBuffer();

		LuaSound(const std::string& Filepath);

	private:

		Ref<AudioBuffer> _Buffer;
	};
}