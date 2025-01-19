#pragma once

#include "Uniform.h"

namespace Volund
{
    class MaterialBlueprint
    {
    public:
        template<typename T>
        void Insert(std::string const& name);
        template<typename T>
        bool Contains(std::string const& name);
        bool Contains(std::string const& name);
        const std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator begin() const;
        const std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator end() const;
    private:
        std::vector<std::shared_ptr<PrimitiveUniform>> m_uniforms;
    };

    template<typename T>
    inline void MaterialBlueprint::Insert(std::string const& name)
    {
        this->m_uniforms.push_back(Uniform<T>::Create(name, T(NULL)));
    }

    template<typename T>
    inline bool MaterialBlueprint::Contains(std::string const& name)
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