#include "PCH/PCH.h"
#include "LuaTexture.h"

namespace Volund
{
	Ref<Texture> LuaTexture::Get()
	{
		return this->_Texture;
	}

	LuaTexture::LuaTexture(const std::string& Filepath)
	{
		this->_Texture = Texture::Create(Filepath);
	}
}