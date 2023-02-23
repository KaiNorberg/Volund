#pragma once

#include "Renderer/Shader/Shader.h"

namespace Volund
{
	struct LuaShader
	{
	public:

		int Padding = NULL;

		Ref<Shader> Get();

		LuaShader(const std::string& ShaderPath);

	private:

		Ref<Shader> _Shader;
	};
}