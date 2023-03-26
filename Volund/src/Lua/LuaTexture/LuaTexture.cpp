#include "PCH/PCH.h"
#include "LuaTexture.h"

namespace Volund
{
	Ref<Texture> LuaTexture::Get()
	{
		return this->m_Texture;
	}

	LuaTexture::LuaTexture(const std::string& filepath)
	{
		this->m_Texture = Texture::Create(filepath);
	}
}