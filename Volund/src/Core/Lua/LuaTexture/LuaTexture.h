#pragma once

#include "Renderer/Texture/Texture.h"

namespace Volund
{
	struct LuaTexture
	{
	public:

		Ref<Texture> Get();

		LuaTexture(const std::string& Filepath);

	private:

		Ref<Texture> _Texture;
	};
}