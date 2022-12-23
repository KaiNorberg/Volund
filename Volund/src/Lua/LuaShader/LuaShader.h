#pragma once

#include "Renderer/Shader/Shader.h"

namespace Volund
{
	struct LuaShader
	{
	public:

		Ref<Shader> Get();

		LuaShader(const std::string& ShaderPath);

	private:

		Ref<Shader> _Shader;
	};
}