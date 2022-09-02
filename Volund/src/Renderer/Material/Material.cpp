#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	Ref<Shader> Material::GetShader()
	{
		return this->_Shader;
	}

	Ref<Material> Material::Create(Ref<Shader> ObjectShader)
	{
		return Ref<Material>(new Material(ObjectShader));
	}

	Material::Material(Ref<Shader> DrawShader)
	{
		this->_Shader = DrawShader;
	}
}