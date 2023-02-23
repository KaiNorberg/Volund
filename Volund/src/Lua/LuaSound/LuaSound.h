#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
	class LuaSound
	{
	public:

		int Padding = NULL;

		Ref<AudioBuffer> GetBuffer();

		LuaSound(const std::string& Filepath);

	private:

		Ref<AudioBuffer> _Buffer;
	};
}