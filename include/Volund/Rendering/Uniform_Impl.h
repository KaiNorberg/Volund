#pragma once

#include "Uniform.h"

#include "../Utils.h"

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
        return this->m_value;
    }

    template<typename T, typename U>
    inline void Uniform<T, U>::Set(const T& value)
    {
        this->m_value = value;
    }

    template<typename T, typename U>
    inline uint64_t Uniform<T, U>::GetTypeId() const
    {
        return Utils::GetTypeId<T>();
    }

    template<typename T, typename U>
    std::shared_ptr<Uniform<T>> Uniform<T, U>::Create(std::string const& name, const T& value)
    {
        return std::shared_ptr<Uniform<T>>(new Uniform<T>(name, value));
    }

    template<typename T, typename U>
    inline Volund::Uniform<T, U>::Uniform(std::string const& name, const T& value)
    {
        this->m_name = name;
        this->m_value = value;
    }
}