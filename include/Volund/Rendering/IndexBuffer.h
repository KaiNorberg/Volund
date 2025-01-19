#pragma once

#include <memory>

namespace Volund
{
    class IndexBuffer
    {
    public:
        virtual void Bind() = 0;

        virtual void Unbind() = 0;

        virtual uint32_t GetCount() const = 0;

        static std::shared_ptr<IndexBuffer> Create(const uint32_t indices[], uint64_t count);

        virtual ~IndexBuffer() = default;
    };
}
