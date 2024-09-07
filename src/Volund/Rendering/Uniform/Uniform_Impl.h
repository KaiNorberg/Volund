#include "Uniform.h"
#pragma once

namespace Volund
{
    template<typename T>
    inline bool PrimitiveUniform::Is() const
    {
        return this->GetTypeId() == Utils::GetTypeId<T>();
    }

    template<typename T>
    inline T& PrimitiveUniform::As()
    {
        if (!this->Is<T>())
        {
            VOLUND_ERROR("Wrong type requested from PrimitiveUniform!");
        }

        return ((Uniform<T>*)this)->Get();
    }

    template<typename T>
    inline void PrimitiveUniform::Set(const T& value)
    {
        if (!this->Is<T>())
        {
            VOLUND_ERROR("Wrong type requested from PrimitiveUniform!");
        }

        return ((Uniform<T>*)this)->Set(value);
    }

    template<typename T, typename U>
    inline T& Uniform<T, U>::Get()
    {
        return this->m_Value;
    }

    template<typename T, typename U>
    inline void Uniform<T, U>::Set(const T& value)
    {
        this->m_Value = value;
    }

    template<typename T, typename U>
    inline uint64_t Uniform<T, U>::GetTypeId() const
    {
        return Utils::GetTypeId<T>();
    }

    template<typename T, typename U>
    Ref<Uniform<T>> Uniform<T, U>::Create(const std::string& name, const T& value)
    {
        return Ref<Uniform<T>>(new Uniform<T>(name, value));
    }

    template<typename T, typename U>
    inline Volund::Uniform<T, U>::Uniform(const std::string& name, const T& value)
    {
        this->m_Name = name;
        this->m_Value = value;
    }
}