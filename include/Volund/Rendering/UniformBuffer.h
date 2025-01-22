#pragma once

#include "UniformBufferBackend.h"

namespace Volund
{
    template<typename T>
    class VOLUND_API UniformBuffer
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