#pragma once

#include "Shader.h"
#include "Texture.h"

namespace Volund
{
    class Material
    {
    public:

        void SetShader(std::shared_ptr<Shader> shader);
        std::shared_ptr<Shader> GetShader();

        std::shared_ptr<MaterialBlueprint> GetBlueprint();

        template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
        void Set(std::string const& name, const T& value);

        template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
        bool Contains(std::string const& name) const;

        void Erase(std::string const& name);

        void UpdateShader();

        std::vector<std::shared_ptr<PrimitiveUniform>>::iterator begin();
        std::vector<std::shared_ptr<PrimitiveUniform>>::iterator end();

        std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator begin() const;
        std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator end() const;

        static std::shared_ptr<Material> Create();
        static std::shared_ptr<Material> Create(std::shared_ptr<Shader> shader);

        Material() = default;
        Material(std::shared_ptr<Shader> shader);

    private:

        std::shared_ptr<Shader> m_shader;

        std::shared_ptr<MaterialBlueprint> m_blueprint;

        std::vector<std::shared_ptr<PrimitiveUniform>> m_uniforms;
    };

    template<typename T, typename>
    inline void Material::Set(std::string const& name, const T& value)
    {
        for (int i = 0; i < this->m_uniforms.size(); i++)
        {
            if (this->m_uniforms[i]->Is<T>() && this->m_uniforms[i]->GetName() == name)
            {
                this->m_uniforms[i]->Set<T>(value);
                return;
            }
        }

        this->m_uniforms.push_back(Uniform<T>::Create(name, value));
    }

    template<typename T, typename>
    inline bool Material::Contains(std::string const& name) const
    {
        for (int i = 0; i < this->m_uniforms.size(); i++)
        {
            if (this->m_uniforms[i]->Is<T>() && this->m_uniforms[i]->GetName() == name)
            {
                return true;
            }
        }

        return false;
    }
}