#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	void Material::SetInt(const std::string& name, UniformInt value)
	{
		if (this->m_Table.Contains<UniformInt>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetFloat(const std::string& name, UniformFloat value)
	{
		if (this->m_Table.Contains<UniformFloat>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetDouble(const std::string& name, UniformDouble value)
	{
		if (this->m_Table.Contains<UniformDouble>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetVec2(const std::string& name, const UniformVec2& value)
	{
		if (this->m_Table.Contains<UniformVec2>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetVec3(const std::string& name, const UniformVec3& value)
	{
		if (this->m_Table.Contains<UniformVec3>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetVec4(const std::string& name, const UniformVec4& value)
	{
		if (this->m_Table.Contains<UniformVec4>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetMat3x3(const std::string& name, const UniformMat3x3& value)
	{
		if (this->m_Table.Contains<UniformMat3x3>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetMat4x4(const std::string& name, const UniformMat4x4& value)
	{
		if (this->m_Table.Contains<UniformMat4x4>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetTexture(const std::string& name, const Ref<Texture>& value)
	{
		if (this->m_Table.Contains<Ref<Texture>>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::SetFramebuffer(const std::string& name, const Ref<Framebuffer>& value)
	{
		if (this->m_Table.Contains<Ref<Framebuffer>>(name))
		{
			this->m_Table[name] = value;
		}
		else
		{
			this->m_Table.Insert(name, value);
		}
	}

	void Material::Erase(const std::string& key)
	{
		this->m_Table.Erase(key);
	}

	void Material::Rename(const std::string& key, const std::string& newKey)
	{
		this->m_Table.Rename(key, newKey);
	}

	const SerialTable::const_iterator Material::begin() const
	{
		return this->m_Table.begin();
	}

	const SerialTable::const_iterator Material::end() const
	{
		return this->m_Table.end();
	}

	SerialTable::iterator Material::begin()
	{
		return this->m_Table.begin();
	}

	SerialTable::iterator Material::end()
	{
		return this->m_Table.end();
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

		int textureUnit = 0;
		for (auto& [name, uniform] : this->m_Table)
		{
			if (uniform->Is<UniformInt>())
			{
				this->m_Shader->SetInt(name, uniform->As<UniformInt>());
			}
			else if (uniform->Is<UniformFloat>())
			{
				this->m_Shader->SetFloat(name, uniform->As<UniformFloat>());
			}
			else if (uniform->Is<UniformDouble>())
			{
				this->m_Shader->SetDouble(name, uniform->As<UniformDouble>());
			}
			else if (uniform->Is<UniformVec2>())
			{
				this->m_Shader->SetVec2(name, uniform->As<UniformVec2>());
			}
			else if (uniform->Is<UniformVec3>())
			{
				this->m_Shader->SetVec3(name, uniform->As<UniformVec3>());
			}
			else if (uniform->Is<UniformVec4>())
			{
				this->m_Shader->SetVec4(name, uniform->As<UniformVec4>());
			}
			else if (uniform->Is<UniformMat3x3>())
			{
				this->m_Shader->SetMat3x3(name, uniform->As<UniformMat3x3>());
			}
			else if (uniform->Is<UniformMat4x4>())
			{
				this->m_Shader->SetMat4x4(name, uniform->As<UniformMat4x4>());
			}
			else if (uniform->Is<UniformTexture>())
			{
				this->m_Shader->SetTexture(name, uniform->As<UniformTexture>(), textureUnit);
				textureUnit++;
			}
			else if (uniform->Is<UniformFramebuffer>())
			{
				this->m_Shader->SetFramebuffer(name, uniform->As<UniformFramebuffer>(), textureUnit);
				textureUnit++;
			}
		}
	}

	void Material::SetShader(Ref<Shader> shader)
	{
		this->m_Shader = shader;

		this->ConformToBlueprint();
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

		/*for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Int))
		{
			if (!this->m_IntUniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (int, %s)", blueprintUniform.c_str());
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

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Matrix))
		{
			if (!this->m_MatrixUniforms.contains(blueprintUniform) && !this->m_FramebufferUniforms.contains(blueprintUniform))
			{
				VOLUND_WARNING("Material does not contain blueprint uniform (sampler, %s)", blueprintUniform.c_str());
			}
		}*/
	}

	void Material::ConformToBlueprint()
	{
		auto blueprint = this->GetBlueprint();

		if (blueprint == nullptr)
		{
			return;
		}

		/*for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Int))
		{
			if (!this->m_IntUniforms.contains(blueprintUniform))
			{
				this->SetInt(blueprintUniform, 0);
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Double))
		{
			if (!this->m_DoubleUniforms.contains(blueprintUniform))
			{
				this->SetDouble(blueprintUniform, 0.0);
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Vec2))
		{
			if (!this->m_Vec2Uniforms.contains(blueprintUniform))
			{
				this->SetVec2(blueprintUniform, Vec2(0.0f));
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Vec3))
		{
			if (!this->m_Vec3Uniforms.contains(blueprintUniform))
			{
				this->SetVec3(blueprintUniform, Vec3(0.0f));
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Vec4))
		{
			if (!this->m_Vec4Uniforms.contains(blueprintUniform))
			{
				this->SetVec4(blueprintUniform, Vec4(0.0f));
			}
		}

		for (auto& blueprintUniform : blueprint->GetUniforms(MaterialUniformType::Sampler))
		{
			if (!this->m_TextureUniforms.contains(blueprintUniform))
			{
				this->SetTexture(blueprintUniform, nullptr);
			}
		}*/
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

		this->ConformToBlueprint();
	}
}
