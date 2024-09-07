#pragma once

#include "Rendering/Shader/Shader.h"
#include "Rendering/Texture/Texture.h"

#include "SerialTable/SerialTable.h"

namespace Volund
{
    class Material
    {
    public:

        void SetShader(Ref<Shader> shader);
        Ref<Shader> GetShader();

        Ref<MaterialBlueprint> GetBlueprint();

        template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
        void Set(const std::string& name, const T& value);
        
        template<typename T, VOLUND_TEMPLATE_UNIFORM_TYPES_ONLY>
        bool Contains(const std::string& name) const;

        void Erase(const std::string& name);

        void UpdateShader();

        std::vector<Ref<PrimitiveUniform>>::iterator begin();
        std::vector<Ref<PrimitiveUniform>>::iterator end();

        std::vector<Ref<PrimitiveUniform>>::const_iterator begin() const;
        std::vector<Ref<PrimitiveUniform>>::const_iterator end() const;

        static Ref<Material> Create();
        static Ref<Material> Create(Ref<Shader> shader);

        Material() = default;
        Material(Ref<Shader> shader);

    private:

        Ref<Shader> m_Shader;

        Ref<MaterialBlueprint> m_Blueprint;

        std::vector<Ref<PrimitiveUniform>> m_Uniforms;
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
