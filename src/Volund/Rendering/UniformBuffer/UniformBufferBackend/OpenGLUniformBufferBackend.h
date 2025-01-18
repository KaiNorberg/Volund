#pragma once

#include "UniformBufferBackend.h"

#include <cstdint>

namespace Volund
{
    class OpenGLUniformBufferBackend : public UniformBufferBackend
    {
    public:

        void SetData(const void* data, uint32_t size, uint32_t offset) override;

        OpenGLUniformBufferBackend(uint32_t size, uint32_t binding);

        ~OpenGLUniformBufferBackend();

    private:

    };
}

