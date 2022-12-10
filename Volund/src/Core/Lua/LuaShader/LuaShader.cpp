#include "PCH/PCH.h"
#include "LuaShader.h"

namespace Volund
{
	Ref<Shader> LuaShader::Get()
	{
		return this->_Shader;
	}

	LuaShader::LuaShader(const std::string& ShaderPath)
	{
		this->_Shader = Shader::Create(ShaderPath);
	}
}