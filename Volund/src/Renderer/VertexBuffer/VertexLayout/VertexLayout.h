#pragma once

namespace Volund
{
	/// <summary>
	/// Binary marked with an x specifiy type, binary marked with a y speccify data size.
	/// xxxyyyyyyyxxx
	/// Unsure if this system will work for an 
	/// </summary>
	enum class VertexAttributeType
	{
		OPENGL_FLOAT  = GL_FLOAT + (1 << 3),
		OPENGL_FLOAT2 = GL_FLOAT + (2 << 3),
		OPENGL_FLOAT3 = GL_FLOAT + (3 << 3),
		OPENGL_FLOAT4 = GL_FLOAT + (4 << 3),
		OPENGL_MAT3   = GL_FLOAT + (9 << 3),
		OPENGL_MAT4   = GL_FLOAT + (12 << 3),
		OPENGL_INT    = GL_INT + (1 << 3),
		OPENGL_INT2   = GL_INT + (2 << 3),
		OPENGL_INT3   = GL_INT + (3 << 3),
		OPENGL_INT4   = GL_INT + (4 << 3)
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

		uint32_t ByteSizeOffset = 0;
		uint32_t BitMask = 0;

		std::string _Name;

		VertexAttributeType _Type;
	};

	typedef std::vector<VertexAttribute> VertexLayout;	
}