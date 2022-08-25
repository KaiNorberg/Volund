#include "PCH/PCH.h"

#include "IndexBuffer.h"

#include "OpenGLIndexBuffer.h"

namespace Volund
{
	uint32_t IndexBuffer::GetCount()
	{
		return this->_Count;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t Indices[], uint32_t Size)
	{
		JSON ConfigFile = JSON::Load(CONFIG_JSON);

		if (ConfigFile["Misc"]["GraphicsAPI"] == "OpenGL")
		{
			return new OpenGLIndexBuffer(Indices, Size);
		}
		else
		{
			VOLUND_ERROR("Unknown GraphicsAPI (%s)", ConfigFile["Misc"]["GraphicsAPI"].GetAs<std::string>().c_str());
			return nullptr;
		}
	}
}