#include "Rendering/Material.hpp"
#include "Instrumentor.hpp"
#include "Lua/LuaAPI.hpp"

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
	
	VOLUND_USERTYPE_REGISTER(Material,
    [](LuaState* state){
        state->NewUsertype<Material>("Material", sol::constructors<>(),
            "new", [](std::shared_ptr<Shader> shader) { return Material::Create(shader); },
            "set_shader", &Material::SetShader,
            "get_shader", &Material::GetShader,
            "contains_int", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<IntUniformType>(name); 
            },
            "contains_float", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<FloatUniformType>(name); 
            },
            "contains_vec2", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Vec2UniformType>(name); 
            },
            "contains_vec3", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Vec3UniformType>(name); 
            },
            "contains_vec4", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Vec4UniformType>(name); 
            },
            "contains_mat4x4", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<Mat4x4UniformType>(name); 
            },
            "contains_texture", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<TextureUniformType>(name); 
            },
            "contains_framebuffer", [](std::shared_ptr<Material> material, std::string const& name) 
            { 
                return material->Contains<FramebufferUniformType>(name); 
            },
            "set_int", [](std::shared_ptr<Material> material, std::string const& name, IntUniformType value)
            {
                material->Set(name, value);
            },
            "set_float", [](std::shared_ptr<Material> material, std::string const& name, FloatUniformType value)
            {
                material->Set(name, value);
            },
            "set_double", [](std::shared_ptr<Material> material, std::string const& name, DoubleUniformType value)
            {
                material->Set(name, value);
            },
            "set_vec2", [](std::shared_ptr<Material> material, std::string const& name, Vec2UniformType value)
            {
                material->Set(name, value);
            },
            "set_vec3", [](std::shared_ptr<Material> material, std::string const& name, Vec3UniformType value)
            {
                material->Set(name, value);
            },
            "set_vec4", [](std::shared_ptr<Material> material, std::string const& name, Vec4UniformType value)
            {
                material->Set(name, value);
            },
            "set_mat4x4", [](std::shared_ptr<Material> material, std::string const& name, Mat4x4UniformType value)
            {
                material->Set(name, value);
            },
            "set_texture", [](std::shared_ptr<Material> material, std::string const& name, TextureUniformType value)
            {
                material->Set(name, value);
            },
            "set_framebuffer", [](std::shared_ptr<Material> material, std::string const& name, FramebufferUniformType value)
            {
                material->Set(name, value);
            }
        );
    });
}