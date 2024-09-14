#pragma once

#include "SerialTable/SerialTable.h"

#include "Rendering/Uniform/Uniform.h"

namespace Volund
{
    class MaterialBlueprint
    {
    public:

        template<typename T>
        void Insert(const std::string& name);

        template<typename T>
        bool Contains(const std::string& name);

        bool Contains(const std::string& name);

        const std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator begin() const;
        const std::vector<std::shared_ptr<PrimitiveUniform>>::const_iterator end() const;

    private:

        std::vector<std::shared_ptr<PrimitiveUniform>> m_Uniforms;
    };

    template<typename T>
    inline void MaterialBlueprint::Insert(const std::string& name)
    {
        this->m_Uniforms.push_back(Uniform<T>::Create(name, T(NULL)));
    }

    template<typename T>
    inline bool MaterialBlueprint::Contains(const std::string& name)
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
