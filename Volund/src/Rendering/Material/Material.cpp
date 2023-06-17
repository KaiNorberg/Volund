#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	void Material::SetInt(const std::string& name, int value)
	{
		this->m_IntUniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetFloat(const std::string& name, float value)
	{
		this->m_FloatUniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetDouble(const std::string& name, double value)
	{
		this->m_DoubleUniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetVec2(const std::string& name, const Vec2& value)
	{
		this->m_Vec2Uniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetVec3(const std::string& name, const Vec3& value)
	{
		this->m_Vec3Uniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetVec4(const std::string& name, const Vec4& value)
	{
		this->m_Vec4Uniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetTexture(const std::string& name, Ref<Texture> value)
	{
		this->m_TextureUniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	void Material::SetFramebuffer(const std::string& name, Ref<Framebuffer> value)
	{
		this->m_FramebufferUniforms[name] = value;
		this->m_MaterialChanged = true;
	}

	std::map<std::string, int>& Material::IntMap()
	{
		return this->m_IntUniforms;
	}

	std::map<std::string, float>& Material::FloatMap()
	{
		return this->m_FloatUniforms;
	}

	std::map<std::string, double>& Material::DoubleMap()
	{
		return this->m_DoubleUniforms;
	}

	std::map<std::string, Vec2>& Material::Vec2Map()
	{
		return this->m_Vec2Uniforms;
	}

	std::map<std::string, Vec3>& Material::Vec3Map()
	{
		return this->m_Vec3Uniforms;
	}

	std::map<std::string, Vec4>& Material::Vec4Map()
	{
		return this->m_Vec4Uniforms;
	}

	std::map<std::string, Ref<Texture>>& Material::TextureMap()
	{
		return this->m_TextureUniforms;
	}

	void Material::UpdateShader()
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_Shader == nullptr)
		{
			return;
		}

		if (this->m_MaterialChanged)
		{
			this->CompareBlueprint();
			this->m_MaterialChanged = false;
		}

		for (auto& [name, value] : this->m_IntUniforms)
		{
			this->m_Shader->SetInt(name, value);
		}

		for (auto& [name, value] : this->m_FloatUniforms)
		{
			this->m_Shader->SetFloat(name, value);
		}

		for (auto& [name, value] : this->m_DoubleUniforms)
		{
			this->m_Shader->SetDouble(name, value);
		}

		for (auto& [name, value] : this->m_Vec2Uniforms)
		{
			this->m_Shader->SetVec2(name, value);
		}

		for (auto& [name, value] : this->m_Vec3Uniforms)
		{
			this->m_Shader->SetVec3(name, value);
		}

		for (auto& [name, value] : this->m_Vec4Uniforms)
		{
			this->m_Shader->SetVec4(name, value);
		}

		int textureUnit = 0;
		for (auto& [name, value] : this->m_TextureUniforms)
		{
			if (value != nullptr)
			{
				this->m_Shader->SetTexture(name, value, textureUnit);
				textureUnit++;
			}
		}
		for (auto& [name, value] : this->m_FramebufferUniforms)
		{
			if (value != nullptr)
			{
				this->m_Shader->SetFramebuffer(name, value, textureUnit);
				textureUnit++;
			}
		}
	}

	void Material::SetShader(Ref<Shader> shader)
	{
		this->m_Shader = shader;
	}

	Ref<Shader> Material::GetShader()
	{
		return this->m_Shader;
	}

	Ref<MaterialBlueprint> Material::GetBlueprint()
	{
		if (this->m_Shader == nullptr)
		{
			return nullptr;
		}
		else
		{
			return this->m_Shader->GetMaterialBlueprint();
		}
	}

	void Material::CompareBlueprint()
	{
		if (this->m_Shader == nullptr)
		{
			return;
		}

		auto& blueprint = this->m_Shader->GetMaterialBlueprint();

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Int))
		{
			if (!this->m_IntUniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (int, %s)", blueprintUniform.c_str());
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Float))
		{
			if (!this->m_FloatUniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (float, %s)", blueprintUniform.c_str());
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Double))
		{
			if (!this->m_DoubleUniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (double, %s)", blueprintUniform.c_str());
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Vec2))
		{
			if (!this->m_Vec2Uniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (vec2, %s)", blueprintUniform.c_str());
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Vec3))
		{
			if (!this->m_Vec3Uniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (vec3, %s)", blueprintUniform.c_str());
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Vec4))
		{
			if (!this->m_Vec4Uniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (vec4, %s)", blueprintUniform.c_str());
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Sampler))
		{
			if (!this->m_TextureUniforms.contains(blueprintUniform) && !this->m_FramebufferUniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (sampler, %s)", blueprintUniform.c_str());
			}
		}
	}

	Ref<Material> Material::Create()
	{
		return std::make_shared<Material>();
	}

	Ref<Material> Material::Create(Ref<Shader> shader)
	{
		return std::make_shared<Material>(shader);
	}

	Material::Material()
	{
	}

	Material::Material(Ref<Shader> shader)
	{
		this->m_Shader = shader;
	}
}
