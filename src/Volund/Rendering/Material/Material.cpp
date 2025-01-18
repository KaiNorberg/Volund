#include "Material.h"

#include "Instrumentor.h"

namespace Volund
{
	void Material::Erase(std::string const& name)
	{
		for (int i = 0; i < this->m_uniforms.size(); i++)
		{
			if (this->m_uniforms[i]->GetName() == name)
			{
				this->m_uniforms.erase(this->m_uniforms.begin() + i);
				return;
			}
		}
	}

	void Material::UpdateShader()
	{
		VOLUND_PROFILE_FUNCTION();

		if (this->m_shader == nullptr)
		{
			return;
		}

		for (int i = 0; i < this->m_uniforms.size(); i++)
		{
			this->m_uniforms[i]->UpdateShader(this->m_shader);
		}
	}

	std::vector<std::shared_ptr<PrimitiveUniform>>::iterator Material::begin()
	{
		return this->m_uniforms.begin();
	}

	std::vector<std::shared_ptr<PrimitiveUniform>>::iterator Material::end()
	{
		return this->m_uniforms.end();
	}

	std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator Material::begin() const
	{
		return this->m_uniforms.begin();
	}

	std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator Material::end() const
	{
		return this->m_uniforms.end();
	}

	void Material::SetShader(std::shared_ptr<Shader> shader)
	{
		this->m_shader = shader;
		this->m_blueprint = shader->GetMaterialBlueprint();

		if (this->m_blueprint == nullptr)
		{
			return;
		}

		for (auto& uniform : (*this->m_blueprint))
		{
			if (uniform->Is<IntUniformType>() && !this->Contains<IntUniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (IntUniformType)NULL);
			}
			else if (uniform->Is<FloatUniformType>() && !this->Contains<FloatUniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (FloatUniformType)NULL);
			}
			else if (uniform->Is<DoubleUniformType>() && !this->Contains<DoubleUniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (DoubleUniformType)NULL);
			}
			else if (uniform->Is<Vec2UniformType>() && !this->Contains<Vec2UniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (Vec2UniformType)NULL);
			}
			else if (uniform->Is<Vec3UniformType>() && !this->Contains<Vec3UniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (Vec3UniformType)NULL);
			}
			else if (uniform->Is<Vec4UniformType>() && !this->Contains<Vec4UniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (Vec4UniformType)NULL);
			}
			else if (uniform->Is<TextureUniformType>() && !this->Contains<TextureUniformType>(uniform->GetName()))
			{
				this->Set(uniform->GetName(), (TextureUniformType)NULL);
			}
		}
	}

	std::shared_ptr<Shader> Material::GetShader()
	{
		return this->m_shader;
	}

	std::shared_ptr<MaterialBlueprint> Material::GetBlueprint()
	{
		if (this->m_shader == nullptr)
		{
			return nullptr;
		}
		else
		{
			return this->m_shader->GetMaterialBlueprint();
		}
	}

	std::shared_ptr<Material> Material::Create()
	{
		return std::make_shared<Material>();
	}

	std::shared_ptr<Material> Material::Create(std::shared_ptr<Shader> shader)
	{
		return std::make_shared<Material>(shader);
	}

	Material::Material(std::shared_ptr<Shader> shader)
	{
		this->SetShader(shader);
	}
}
