#include "PCH/PCH.h"

#include "VertexLayout.h"

#include "Renderer/Renderer.h"

namespace Volund
{
	uint32_t VertexAttribute::GetDataType() const
	{
		return (this->BitMask & (int)this->_Type);
	}

	uint32_t VertexAttribute::GetByteSize() const
	{
		return this->GetElementCount() * 4 /*Size of float and uint32_t is 4 bytes*/;
	}

	uint32_t VertexAttribute::GetElementCount() const
	{
		return ((~this->BitMask) & (int)this->_Type) >> this->ByteSizeOffset;
	}

	std::string VertexAttribute::GetName() const
	{
		return this->_Name;
	}

	VertexAttribute::VertexAttribute(VertexAttributeType Type, std::string Name) : _Type(Type), _Name(Name)
	{
		switch (Renderer::GetGraphicsAPI())
		{
		case GraphicsAPI::OPENGL:
		{
			this->ByteSizeOffset = 3;
			this->BitMask = 0b1110000000111;		
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