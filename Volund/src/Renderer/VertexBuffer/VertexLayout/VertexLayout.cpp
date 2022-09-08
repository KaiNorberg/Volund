#include "PCH/PCH.h"

#include "VertexLayout.h"

#include "Renderer/RenderingAPI/RenderingAPI.h"

#include <glad/include/glad/glad.h>

namespace Volund
{
	uint32_t VertexAttribute::GetDataType() const
	{
		return this->FloatID * (((int)this->_Type & VOLUND_ATTRIBUTE_FLOAT) >> 1) + this->IntID * ((int)this->_Type &
			VOLUND_ATTRIBUTE_INT);
	}

	uint32_t VertexAttribute::GetByteSize() const
	{
		return this->GetElementCount() * 4 /*Size of float and uint32_t is 4 bytes*/;
	}

	uint32_t VertexAttribute::GetElementCount() const
	{
		return ((int)this->_Type >> 2);
	}

	std::string VertexAttribute::GetName() const
	{
		return this->_Name;
	}

	VertexAttribute::VertexAttribute(VertexAttributeType Type, std::string Name) : _Name(Name), _Type(Type)
	{
		switch (RenderingAPI::GetSelectedAPI())
		{
		case RenderingAPI::API::OPENGL:
			{
				this->FloatID = GL_FLOAT;
				this->IntID = GL_INT;
			}
			break;
		default:
			{
				VOLUND_ERROR("Creating a VertexAttribute without a specified GraphicsAPI!");
			}
			break;
		}
	}
}
