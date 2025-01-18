#include "MaterialBlueprint.h"

namespace Volund
{
	bool MaterialBlueprint::Contains(std::string const& name)
	{
		for (auto& uniform : this->m_uniforms)
		{
			if (uniform->GetName() == name)
			{
				return true;
			}
		}

		return false;
	}

	const std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator MaterialBlueprint::begin() const
	{
		return this->m_uniforms.begin();
	}

	const std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator MaterialBlueprint::end() const
	{
		return this->m_uniforms.end();
	}
}
