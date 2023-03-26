#pragma once

#include "Renderer/Texture/Texture.h"

namespace Volund
{
	struct LuaTexture
	{
	public:

		int Padding = NULL;

		Ref<Texture> Get();

		LuaTexture(const std::string& filepath);

	private:

		Ref<Texture> m_Texture;
	};
}