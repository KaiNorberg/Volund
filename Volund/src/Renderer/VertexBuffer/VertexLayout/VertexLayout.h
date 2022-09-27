#pragma once

#define VOLUND_ATTRIBUTE_FLOAT 0b10
#define VOLUND_ATTRIBUTE_INT   0b01

namespace Volund
{
	enum class VertexAttributeType
	{
		FLOAT = VOLUND_ATTRIBUTE_FLOAT + (1 << 2),
		FLOAT2 = VOLUND_ATTRIBUTE_FLOAT + (2 << 2),
		FLOAT3 = VOLUND_ATTRIBUTE_FLOAT + (3 << 2),
		FLOAT4 = VOLUND_ATTRIBUTE_FLOAT + (4 << 2),
		MAT3 = VOLUND_ATTRIBUTE_FLOAT + (9 << 2),
		MAT4 = VOLUND_ATTRIBUTE_FLOAT + (12 << 2),
		INT = VOLUND_ATTRIBUTE_INT + (1 << 2),
		INT2 = VOLUND_ATTRIBUTE_INT + (2 << 2),
		INT3 = VOLUND_ATTRIBUTE_INT + (3 << 2),
		INT4 = VOLUND_ATTRIBUTE_INT + (4 << 2)
	};

	class VertexAttribute
	{
	public:

		uint32_t GetDataType() const;

		uint32_t GetByteSize() const;

		uint32_t GetElementCount() const;

		std::string GetName() const;

		VertexAttribute(VertexAttributeType Type, std::string Name = "");

	private:

		std::string _Name;

		VertexAttributeType _Type;
	};

	using VertexLayout = std::vector<VertexAttribute>;
}
