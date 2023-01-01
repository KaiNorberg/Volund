#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	std::string Material::GetFilepath()
	{
		return this->_Filepath;
	}

	void Material::SetInt(const std::string& Name, int Value)
	{
		this->_IntUniforms[Name] = Value;
	}

	void Material::SetFloat(const std::string& Name, float Value)
	{
		this->_FloatUniforms[Name] = Value;
	}

	void Material::SetDouble(const std::string& Name, double Value)
	{
		this->_DoubleUniforms[Name] = Value;
	}

	void Material::SetVec2(const std::string& Name, const Vec2& Value)
	{
		this->_Vec2Uniforms[Name] = Value;
	}

	void Material::SetVec3(const std::string& Name, const Vec3& Value)
	{
		this->_Vec3Uniforms[Name] = Value;
	}

	void Material::SetTexture(const std::string& Name, Ref<Texture> Value)
	{
		this->_TextureUniforms[Name] = Value;
	}

	void Material::UpdateShader()
	{
		VOLUND_PROFILE_FUNCTION();

		for (auto& [Name, Value] : this->_IntUniforms)
		{
			this->_Shader->SetInt(Name, Value);
		}

		for (auto& [Name, Value] : this->_FloatUniforms)
		{
			this->_Shader->SetFloat(Name, Value);
		}

		for (auto& [Name, Value] : this->_DoubleUniforms)
		{
			this->_Shader->SetDouble(Name, Value);
		}

		for (auto& [Name, Value] : this->_Vec2Uniforms)
		{
			this->_Shader->SetVec2(Name, Value);
		}

		for (auto& [Name, Value] : this->_Vec3Uniforms)
		{
			this->_Shader->SetVec3(Name, Value);
		}

		int TextureUnit = 0;
		for (auto& [Name, Value] : this->_TextureUniforms)
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
