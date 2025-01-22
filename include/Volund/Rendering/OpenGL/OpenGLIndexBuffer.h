#pragma once

#include "../IndexBuffer.h"

namespace Volund
{
    class VOLUND_API OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        void Bind() override;
        void Unbind() override;
        uint32_t GetCount() const override;
        OpenGLIndexBuffer(const uint32_t indices[], uint64_t count);
        ~OpenGLIndexBuffer() override;
    private:
        uint32_t m_count;
        uint32_t m_id;
    };
}