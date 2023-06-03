#include "PCH/PCH.h"
#include "Material.h"

namespace Volund
{
	void Material::SetInt(const std::string& name, int value)
	{
		this->m_IntUniforms[name] = value;
	}

	void Material::SetFloat(const std::string& name, float value)
	{
		this->m_FloatUniforms[name] = value;
	}

	void Material::SetDouble(const std::string& name, double value)
	{
		this->m_DoubleUniforms[name] = value;
	}

	void Material::SetVec2(const std::string& name, const Vec2& value)
	{
		this->m_Vec2Uniforms[name] = value;
	}

	void Material::SetVec3(const std::string& name, const Vec3& value)
	{
		this->m_Vec3Uniforms[name] = value;
	}

	void Material::SetVec4(const std::string& name, const Vec4& value)
	{
		this->m_Vec4Uniforms[name] = value;
	}

	void Material::SetTexture(const std::string& name, Ref<Texture> value)
	{
		this->m_TextureUniforms[name] = value;
	}

	void Material::SetFramebuffer(const std::string& name, Ref<Framebuffer> value)
	{
		this->m_FramebufferUniforms[name] = value;
	}

	void Material::UpdateShader()
	{
		VOLUND_PROFILE_FUNCTION();

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
			this->m_Shader->SetTexture(name, value, textureUnit);
			textureUnit++;
		}
		for (auto& [name, value] : this->m_FramebufferUniforms)
		{
			this->m_Shader->SetFramebuffer(name, value, textureUnit);
			textureUnit++;
		}
	}

	Ref<Shader> Material::GetShader()
	{
		return this->m_Shader;
	}

	Ref<Material> Material::Create(Ref<Shader> shader)
	{
		return std::make_shared<Material>(shader);
	}

	Material::Material(Ref<Shader> shader)
	{
		this->m_Shader = shader;
	}
}
