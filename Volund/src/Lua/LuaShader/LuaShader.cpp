#include "PCH/PCH.h"
#include "LuaShader.h"

namespace Volund
{
	Ref<Shader> LuaShader::Get()
	{
		return this->m_Shader;
	}

	LuaShader::LuaShader(const std::string& filepath)
	{
		this->m_Shader = Shader::Create(filepath);
	}
}