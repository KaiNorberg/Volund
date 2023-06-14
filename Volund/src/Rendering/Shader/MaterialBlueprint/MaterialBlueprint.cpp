#include "PCH/PCH.h"
#include "MaterialBlueprint.h"

namespace Volund
{
	void MaterialBlueprint::AddUniform(const std::string& name, MaterialUniformType type)
	{
		this->m_Uniforms[(int)type].push_back(name);
	}

	const std::vector<std::string>& MaterialBlueprint::GetUniforms(MaterialUniformType type) const
	{
		return this->m_Uniforms[(int)type];
	}

	MaterialBlueprint::MaterialBlueprint()
	{
		this->m_Uniforms.resize((int)MaterialUniformType::AMOUNT);
	}
}
