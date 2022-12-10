#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	std::string Material::GetFilepath()
	{
		return this->_Filepath;
	}

	Ref<Texture> Material::GetTexture(const std::string& Name)
	{
		if (this->HasTexture(Name))
		{
			return this->_Textures[Name];
		}
		else
		{
			return nullptr;
		}
	}

	void Material::SetTexture(const std::string& Name, Ref<Texture> Value)
	{
		this->_Textures[Name] = Value;
	}

	bool Material::HasTexture(const std::string& Name)
	{
		return this->_Textures.contains(Name);
	}

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

		int TextureUnit = 0;
		for (auto& [Name, Value] : this->_Textures)
		{
			this->_Shader->SetTexture(Name, Value, TextureUnit);
			TextureUnit++;
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
