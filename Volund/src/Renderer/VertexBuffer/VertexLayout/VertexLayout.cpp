#include "PCH/PCH.h"

#include "VertexLayout.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	uint32_t VertexAttribute::GetDataType() const
	{	
		uint32_t FloatID;
		uint32_t IntID;

		switch (RenderingAPI::GetSelectedAPI())
		{
			case RenderingAPI::API::OPENGL:
			{
				FloatID = GL_FLOAT;
				IntID = GL_INT;
			}
			break;
			default:
			{
				VOLUND_ERROR("Unknown API in VertexAttribute!");
			}
			break;
		}

		return FloatID * (((uint32_t)this->_Type & VOLUND_ATTRIBUTE_FLOAT) >> 1) + IntID * ((uint32_t)this->_Type &
			VOLUND_ATTRIBUTE_INT);
	}

	uint32_t VertexAttribute::GetByteSize() const
	{
		return this->GetElementCount() * 4 /*Size of float and uint32_t is 4 bytes*/;
	}

	uint32_t VertexAttribute::GetElementCount() const
	{
		return ((uint32_t)this->_Type >> 2);
	}

	std::string VertexAttribute::GetName() const
	{
		return this->_Name;
	}

	VertexAttribute::VertexAttribute(VertexAttributeType Type, std::string Name)
	{
		this->_Type = Type;
		this->_Name = Name;
	}
}
