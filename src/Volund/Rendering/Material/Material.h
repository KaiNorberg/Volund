#pragma once

#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture.h"

#include "SerialTable/SerialTable.h"

namespace Volund
{
    class Material
    {
    public:

        void SetShader(std::shared_ptr<Shader> shader);
        std::shared_ptr<Shader> GetShader();

        std::shared_ptr<MaterialBlueprint> GetBlueprint();

        template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
        void Set(const std::string& name, const T& value);

        template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
        bool Contains(const std::string& name) const;

        void Erase(const std::string& name);

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

        std::shared_ptr<Shader> m_Shader;

        std::shared_ptr<MaterialBlueprint> m_Blueprint;

        std::vector<std::shared_ptr<PrimitiveUniform>> m_Uniforms;
    };

    template<typename T, typename>
    inline void Material::Set(const std::string& name, const T& value)
    {
        for (int i = 0; i < this->m_Uniforms.size(); i++)
        {
            if (this->m_Uniforms[i]->Is<T>() && this->m_Uniforms[i]->GetName() == name)
            {
                this->m_Uniforms[i]->Set<T>(value);
                return;
            }
        }

        this->m_Uniforms.push_back(Uniform<T>::Create(name, value));
    }

    template<typename T, typename>
    inline bool Material::Contains(const std::string& name) const
    {
        for (int i = 0; i < this->m_Uniforms.size(); i++)
        {
            if (this->m_Uniforms[i]->Is<T>() && this->m_Uniforms[i]->GetName() == name)
            {
                return true;
            }
        }

        return false;
    }
}
