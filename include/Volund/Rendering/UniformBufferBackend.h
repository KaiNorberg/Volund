#pragma once

#include "../Core.h"

#include <cstdint>
#include <memory>

namespace Volund
{
    class VOLUND_API UniformBufferBackend
    {
    public:
        virtual void SetData(const void* data, uint32_t size, uint32_t offset) = 0;
        static std::shared_ptr<UniformBufferBackend> Create(uint32_t size, uint32_t binding);
        virtual ~UniformBufferBackend();
    protected:
        uint32_t m_id = 0;
    private:
    };
}
