#include "PCH/PCH.h"
#include "LuaSound.h"

namespace Volund
{
	Ref<AudioBuffer> LuaSound::GetBuffer()
	{
		return this->_Buffer;
	}

	LuaSound::LuaSound(const std::string& Filepath)
	{
		this->_Buffer = std::make_shared<AudioBuffer>(Filepath);
	}
}