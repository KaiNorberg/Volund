#include "PCH/PCH.h"
#include "LuaSound.h"

namespace Volund
{
	Ref<AudioBuffer> LuaSound::GetBuffer()
	{
		return this->m_Buffer;
	}

	LuaSound::LuaSound(const std::string& filepath)
	{
		this->m_Buffer = std::make_shared<AudioBuffer>(filepath);
	}
}