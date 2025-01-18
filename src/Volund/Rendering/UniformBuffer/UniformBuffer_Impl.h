#pragma once

namespace Volund
{
    template<typename T>
    T* UniformBuffer<T>::operator->()
    {
        return &this->m_data;
    }

    template<typename T>
    inline void UniformBuffer<T>::Update()
    {
        this->m_backend->SetData(&this->m_data, sizeof(T), 0);
    }

    template<typename T>
    inline UniformBuffer<T>::UniformBuffer(uint32_t binding)
    {
        this->m_backend = UniformBufferBackend::Create(sizeof(T), binding);
    }
}