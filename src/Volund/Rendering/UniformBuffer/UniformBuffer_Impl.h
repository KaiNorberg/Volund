#pragma once

namespace Volund
{
    template<typename T>
    T* UniformBuffer<T>::operator->()
    {
        return &this->m_Data;
    }

    template<typename T>
    inline void UniformBuffer<T>::Update()
    {
        this->m_Backend->SetData(&this->m_Data, sizeof(T), 0);
    }

    template<typename T>
    inline UniformBuffer<T>::UniformBuffer(uint32_t binding)
    {
        this->m_Backend = UniformBufferBackend::Create(sizeof(T), binding);
    }
}