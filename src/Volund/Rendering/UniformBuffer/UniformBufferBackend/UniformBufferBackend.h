#pragma once

namespace Volund
{
    class UniformBufferBackend
    {
    public:

        virtual void SetData(const void* data, uint32_t size, uint32_t offset) = 0;

        static std::shared_ptr<UniformBufferBackend> Create(uint32_t size, uint32_t binding);

        virtual ~UniformBufferBackend();

    protected:

        uint32_t m_Id = 0;

    private:
    };
}
