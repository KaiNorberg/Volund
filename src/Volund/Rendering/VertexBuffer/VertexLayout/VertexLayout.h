#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define VOLUND_ATTRIBUTE_FLOAT 0b10
#define VOLUND_ATTRIBUTE_INT   0b01

namespace Volund
{
    enum class VertexAttributeType
    {
        Float = VOLUND_ATTRIBUTE_FLOAT + (1 << 2),
        Float2 = VOLUND_ATTRIBUTE_FLOAT + (2 << 2),
        Float3 = VOLUND_ATTRIBUTE_FLOAT + (3 << 2),
        Float4 = VOLUND_ATTRIBUTE_FLOAT + (4 << 2),
        Mat3 = VOLUND_ATTRIBUTE_FLOAT + (9 << 2),
        Mat4 = VOLUND_ATTRIBUTE_FLOAT + (12 << 2),
        Int = VOLUND_ATTRIBUTE_INT + (1 << 2),
        Int2 = VOLUND_ATTRIBUTE_INT + (2 << 2),
        Int3 = VOLUND_ATTRIBUTE_INT + (3 << 2),
        Int4 = VOLUND_ATTRIBUTE_INT + (4 << 2)
    };

    class VertexAttribute
    {
    public:

        uint32_t GetDataType() const;

        uint32_t GetByteSize() const;

        uint32_t GetElementCount() const;

        std::string GetName() const;

        VertexAttribute(VertexAttributeType type, std::string name = "");

    private:

        std::string m_Name;

        VertexAttributeType m_Type;
    };

    using VertexLayout = std::vector<VertexAttribute>;
}
