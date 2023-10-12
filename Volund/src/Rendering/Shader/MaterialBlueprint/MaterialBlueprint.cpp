#include "PCH/PCH.h"
#include "MaterialBlueprint.h"

namespace Volund
{
	uint64_t MaterialBlueprint::BlueprintUniform::GetTypeHash() const
	{
		return this->m_TypeHash;
	}
	const std::string& MaterialBlueprint::BlueprintUniform::GetName() const
	{
		return this->m_Name;
	}

	MaterialBlueprint::BlueprintUniform::BlueprintUniform(uint64_t typeHash, const std::string& name)
	{
		this->m_TypeHash = typeHash;
		this->m_Name = name;
	}

	bool MaterialBlueprint::Exists(const std::string& name)
	{
		for (auto& uniform : this->m_Uniforms)
		{
			if (uniform.GetName() == name)
			{
				return true;
			}
		}

		return false;
	}

	const std::vector<MaterialBlueprint::BlueprintUniform>::const_iterator MaterialBlueprint::begin() const
	{
		return this->m_Uniforms.begin();
	}

	const std::vector<MaterialBlueprint::BlueprintUniform>::const_iterator MaterialBlueprint::end() const
	{
		return this->m_Uniforms.end();
	}
}
