#pragma once

#include "Audio/AudioBuffer/AudioBuffer.h"

namespace Volund
{
	class LuaSound
	{
	public:

		int Padding = 0;

		Ref<AudioBuffer> GetBuffer();

		LuaSound(const std::string& filepath);

	private:

		Ref<AudioBuffer> m_Buffer;
	};
}