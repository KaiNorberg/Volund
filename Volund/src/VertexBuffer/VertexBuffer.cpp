#include "PCH/PCH.h"

#include "VertexBuffer.h"

#include "OpenGLVertexBuffer.h"

namespace Volund
{
	uint32_t VertexBuffer::GetCount()
	{
		return this->_Count;
	}

	VertexBuffer* VertexBuffer::Create(float Vertices[], uint32_t Count)
	{
		JSON ConfigFile = JSON::Load(CONFIG_JSON);

		if (ConfigFile["Misc"]["GraphicsAPI"] == "OpenGL")
		{
			return new OpenGLVertexBuffer(Vertices, Count);
		}
		else
		{
			VOLUND_ERROR("Unknown GraphicsAPI (%s)", ConfigFile["Misc"]["GraphicsAPI"].GetAs<std::string>().c_str());
			return nullptr;
		}
	}
}