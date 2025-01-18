#pragma once

#include "UniformBufferBackend/UniformBufferBackend.h"

namespace Volund
{
    template<typename T>
    class UniformBuffer
    {
    public:

        T* operator ->();

        void Update();

        UniformBuffer(uint32_t binding);

    private:

        std::shared_ptr<UniformBufferBackend> m_backend;

        T m_data;
    };
}

#include "UniformBuffer_Impl.h"
