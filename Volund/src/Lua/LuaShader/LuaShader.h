#pragma once

#include "Renderer/Shader/Shader.h"

namespace Volund
{
	struct LuaShader
	{
	public:

		int Padding = NULL;

		Ref<Shader> Get();

		LuaShader(const std::string& filepath);

	private:

		Ref<Shader> m_Shader;
	};
}