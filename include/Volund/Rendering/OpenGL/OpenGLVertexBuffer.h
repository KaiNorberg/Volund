#pragma once

#include "../VertexBuffer.h"

namespace Volund
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        
        AABB GetAABB() override;

        void Bind() override;

        void Unbind() override;

        uint32_t GetCount() override;

        void SetLayout(const VertexLayout& layout) override;

        VertexLayout GetLayout() override;

        OpenGLVertexBuffer(const float vertices[], uint64_t count);

        ~OpenGLVertexBuffer() override;

    private:

        AABB m_aABB = {};

        VertexLayout m_layout;
        
        uint32_t m_count;

        uint32_t m_id;
    };
}