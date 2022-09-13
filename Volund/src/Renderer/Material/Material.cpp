#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	void Material::UpdateShader()
	{
		for (auto& Value : this->View<int>())
		{
			this->_Shader->SetInt(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<float>())
		{
			this->_Shader->SetFloat(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<double>())
		{
			this->_Shader->SetDouble(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<Vec2>())
		{
			this->_Shader->SetVec2(Value->GetName(), Value->GetValue());
		}

		for (auto& Value : this->View<Vec3>())
		{
			this->_Shader->SetVec3(Value->GetName(), Value->GetValue());
		}
	}

	Ref<Shader> Material::GetShader()
	{
		return this->_Shader;
	}

	Ref<Material> Material::Create(Ref<Shader> ObjectShader)
	{
		return std::make_shared<Material>(ObjectShader);
	}

	Material::Material(Ref<Shader> DrawShader)
	{
		this->_Shader = DrawShader;
	}
}
