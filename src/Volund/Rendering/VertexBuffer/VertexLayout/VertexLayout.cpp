
#include "VertexLayout.h"

#include "Rendering/RenderingAPI/RenderingAPI.h"

#include <glad/glad.h>

namespace Volund
{
	uint32_t VertexAttribute::GetDataType() const
	{
		uint32_t floatId;
		uint32_t intId;

		switch (RenderingAPI::GetSelectedAPI())
		{
			case GraphicsAPI::OpenGL:
			{
				floatId = GL_FLOAT;
				intId = GL_INT;
			}
			break;
			default:
			{
				VOLUND_ERROR("Unknown API in VertexAttribute!");
			}
			break;
		}

		return floatId * (((uint32_t)this->m_type & VOLUND_ATTRIBUTE_FLOAT) >> 1) + intId * ((uint32_t)this->m_type &
			VOLUND_ATTRIBUTE_INT);
	}

	uint32_t VertexAttribute::GetByteSize() const
	{
		return this->GetElementCount() * 4 /*Size of float and uint32_t is 4 bytes*/;
	}

	uint32_t VertexAttribute::GetElementCount() const
	{
		return ((uint32_t)this->m_type >> 2);
	}

	std::string VertexAttribute::GetName() const
	{
		return this->m_name;
	}

	VertexAttribute::VertexAttribute(const VertexAttributeType type, const std::string name)
	{
		this->m_type = type;
		this->m_name = name;
	}
}
