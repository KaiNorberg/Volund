#pragma once

#include "VertexLayout.h"

#include "../AABB.h"

namespace Volund
{
    class VOLUND_API VertexBuffer
    {
    public:
        virtual AABB GetAABB() = 0;
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual uint32_t GetCount() = 0;
        virtual void SetLayout(const VertexLayout& layout) = 0;
        virtual VertexLayout GetLayout() = 0;
        static std::shared_ptr<VertexBuffer> Create(const float vertices[], uint64_t count);
        virtual ~VertexBuffer() = default;
    };
}